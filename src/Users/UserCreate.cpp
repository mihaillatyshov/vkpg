#include "UserCreate.hpp"

#include "User.hpp"

#include <fmt/format.h>
#include <string>
#include <vector>

#include <userver/clients/dns/component.hpp>
#include <userver/formats/json.hpp>
#include <userver/server/handlers/http_handler_json_base.hpp>
#include <userver/storages/postgres/cluster.hpp>
#include <userver/storages/postgres/component.hpp>
#include <userver/utils/assert.hpp>
#include <userver/utils/fixed_array.hpp>

namespace vkpg {

namespace {

class UserCreate final : public userver::server::handlers::HttpHandlerJsonBase {
 public:
  static constexpr std::string_view kName = "handler-user-create";

  UserCreate(const userver::components::ComponentConfig& config,
             const userver::components::ComponentContext& component_context)
      : HttpHandlerJsonBase(config, component_context),
        m_PGCluster(
            component_context
                .FindComponent<userver::components::Postgres>("postgres-db-1")
                .GetCluster()) {}

  userver::formats::json::Value HandleRequestJsonThrow(
      const userver::server::http::HttpRequest& request,
      const userver::formats::json::Value& json,
      userver::server::request::RequestContext&) const override {
    const auto& nickname = request.GetPathArg("nickname");

    const auto fullname = json["fullname"].As<std::string>("");
    const auto about = json["about"].As<std::string>("");
    const auto email = json["email"].As<std::string>("");

    if (!nickname.empty() && !fullname.empty() && !email.empty()) {
      try {
        auto result = m_PGCluster->Execute(
            userver::storages::postgres::ClusterHostType::kMaster,
            "INSERT INTO tp.users(nickname, fullname, about, email) "
            "VALUES($1, $2, $3, $4) "
            "RETURNING nickname, fullname, about, email ",
            nickname, fullname, about, email);
        return userver::formats::json::MakeObject("nickname", nickname,  //
                                                  "fullname", fullname,  //
                                                  "about", about,        //
                                                  "email", email);
      } catch (...) {
        auto result = m_PGCluster->Execute(
            userver::storages::postgres::ClusterHostType::kMaster,
            "SELECT nickname, fullname, about, email FROM tp.users "
            "WHERE nickname = $1 OR email = $2 ",
            nickname, email);
        auto users =
            result.AsSetOf<UserTypePG>(userver::storages::postgres::kRowTag);
        userver::formats::json::ValueBuilder builder;
        for (const auto& user : users) {
          builder.PushBack(userver::formats::json::MakeObject(
              "nickname", std::get<0>(user),  //
              "fullname", std::get<1>(user),  //
              "about", std::get<2>(user),     //
              "email", std::get<3>(user)));
        }
        request.SetResponseStatus(userver::server::http::HttpStatus::kConflict);
        return builder.ExtractValue();
      }
    }

    request.SetResponseStatus(userver::server::http::HttpStatus::kBadRequest);
    return userver::formats::json::MakeObject("message", "error");
  }

  userver::storages::postgres::ClusterPtr m_PGCluster;
};

}  // namespace

void AppendUserCreate(userver::components::ComponentList& component_list) {
  component_list.Append<UserCreate>();
}

}  // namespace vkpg
#include "ForumCreate.hpp"

#include "Forum.hpp"

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

class ForumCreate final
    : public userver::server::handlers::HttpHandlerJsonBase {
 public:
  static constexpr std::string_view kName = "handler-forum-create";

  ForumCreate(const userver::components::ComponentConfig& config,
              const userver::components::ComponentContext& component_context)
      : HttpHandlerJsonBase(config, component_context),
        m_ClusterPG(
            component_context
                .FindComponent<userver::components::Postgres>("postgres-db-1")
                .GetCluster()) {}

  userver::formats::json::Value HandleRequestJsonThrow(
      const userver::server::http::HttpRequest& request,
      const userver::formats::json::Value& json,
      userver::server::request::RequestContext&) const override {
    const auto title = json["title"].As<std::string>("");
    const auto nickname = json["user"].As<std::string>("");
    const auto slug = json["slug"].As<std::string>("");

    if (title.empty() || nickname.empty() || slug.empty()) {
      request.SetResponseStatus(userver::server::http::HttpStatus::kBadRequest);
      return userver::formats::json::MakeObject("message", "bad data");
    }
    request.SetResponseStatus(userver::server::http::HttpStatus::kBadRequest);
    return userver::formats::json::MakeObject("message", "bad data");

    // try {
    //   auto result = m_ClusterPG->Execute(
    //       userver::storages::postgres::ClusterHostType::kMaster,
    //       "INSERT INTO tp.forum(title, slug, user) "
    //       "VALUES($1, $2, $3, $4) "
    //       "RETURNING nickname, fullname, about, email",
    //       nickname, fullname, about, email);
    //   const auto& user =
    //       result.AsSingleRow<UserTypePG>(userver::storages::postgres::kRowTag);
    //   request.SetResponseStatus(userver::server::http::HttpStatus::kCreated);
    //   return MakeUserJson(user);
    // } catch (...) {
    //   auto result = m_ClusterPG->Execute(
    //       userver::storages::postgres::ClusterHostType::kMaster,
    //       "SELECT nickname, fullname, about, email FROM tp.users "
    //       "WHERE lower(nickname) = lower($1) OR lower(email) = lower($2) ",
    //       nickname, email);
    //   auto users =
    //       result.AsSetOf<UserTypePG>(userver::storages::postgres::kRowTag);
    //   userver::formats::json::ValueBuilder builder;
    //   for (const auto& user : users) {
    //     builder.PushBack(MakeUserJson(user));
    //   }
    //   request.SetResponseStatus(userver::server::http::HttpStatus::kConflict);
    //   return builder.ExtractValue();
    // }
  }

 private:
  userver::storages::postgres::ClusterPtr m_ClusterPG;
};

}  // namespace

void AppendForumCreate(userver::components::ComponentList& component_list) {
  component_list.Append<ForumCreate>();
}

}  // namespace vkpg
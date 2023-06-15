#include "UserCreate.hpp"

#include <fmt/format.h>

#include <userver/clients/dns/component.hpp>
#include <userver/formats/json.hpp>
#include <userver/server/handlers/http_handler_base.hpp>
#include <userver/storages/postgres/cluster.hpp>
#include <userver/storages/postgres/component.hpp>
#include <userver/utils/assert.hpp>

namespace vkpg {

namespace {

class UserCreate final : public userver::server::handlers::HttpHandlerBase {
 public:
  static constexpr std::string_view kName = "handler-user-create";

  Hello(const userver::components::ComponentConfig& config,
        const userver::components::ComponentContext& component_context)
      : HttpHandlerBase(config, component_context),
        pg_cluster_(
            component_context
                .FindComponent<userver::components::Postgres>("postgres-db-1")
                .GetCluster()) {}

  std::string HandleRequestThrow(
      const userver::server::http::HttpRequest& request,
      userver::server::request::RequestContext&) const override {
    const auto& nickname = request.GetArg("nickname");
    formats::json::Value json =
        userver::formats::json::FromString(request.RequestBody());
    const auto fullname = json["fullname"].As<std::string>("");
    const auto about = json["about"].As<std::string>();
    const auto email = json["email"].As<std::string>("");

    if (!name.empty() && !fullname.empty(), &&!email.empty()) {
      auto result = pg_cluster_->Execute(
          userver::storages::postgres::ClusterHostType::kMaster,
          "INSERT INTO tp.users(nickname, fullname, about, email)"
          "VALUES($1, $2, $3, $4)",
          nickname, fullname, about, email);
      return "Created!"
    }

    return "Error!"
  }

  userver::storages::postgres::ClusterPtr m_PGCluster;
};

void AppendUserCreate(userver::components::ComponentList& component_list) {
  component_list.Append<UserCreate>();
}

}  // namespace
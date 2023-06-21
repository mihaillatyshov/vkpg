#include "Thread.hpp"

namespace vkpg {

namespace Thread {

userver::formats::json::Value MakeJson(int id,                    //
                                       std::string_view title,    //
                                       std::string_view message,  //
                                       std::string_view slug,     //
                                       int votes,                 //
                                       std::string_view author,   //
                                       std::string_view forum,    //
                                       std::string_view created) {
  userver::formats::json::ValueBuilder builder;
  builder["id"] = id;
  builder["title"] = title;
  builder["message"] = message;
  builder["slug"] = slug;
  builder["votes"] = votes;
  builder["author"] = author;
  builder["forum"] = forum;
  builder["created"] = created;

  return builder.ExtractValue();
}

userver::formats::json::Value MakeJson(const TypePG& thread) {
  return MakeJson(std::get<0>(thread),  //
                  std::get<1>(thread),  //
                  std::get<2>(thread),  //
                  std::get<3>(thread),  //
                  std::get<4>(thread),  //
                  std::get<5>(thread),  //
                  std::get<6>(thread),  //
                  std::get<7>(thread));
}

userver::formats::json::Value MakeJson(const TypeNoUserNoForumPG& thread,
                                       std::string_view author,
                                       std::string_view forum) {
  return MakeJson(std::get<0>(thread),  //
                  std::get<1>(thread),  //
                  std::get<2>(thread),  //
                  std::get<3>(thread),  //
                  std::get<4>(thread),  //
                  author,               //
                  forum,                //
                  std::get<5>(thread));
}

userver::storages::postgres::ResultSet SelectBySlug(
    const userver::storages::postgres::ClusterPtr& cluster,
    std::string_view slug) {
  return cluster->Execute(userver::storages::postgres::ClusterHostType::kMaster,
                          "SELECT t.id, t.title, t.message, t.slug, t.votes, "
                          "u.nickname, f.slug, t.created_at "
                          "FROM tp.threads AS t "
                          "JOIN tp.forums AS f ON t.forum_id = f.id "
                          "JOIN tp.users AS u ON t.user_id = u.id "
                          "WHERE lower(t.slug) = lower($1) ",
                          slug);
}

}  // namespace Thread

}  // namespace vkpg
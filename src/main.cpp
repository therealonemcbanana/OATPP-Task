#include "AppComponent.hpp"
#include "controller/NoteController.hpp"
#include "oatpp-swagger/Controller.hpp"
#include "oatpp/network/Server.hpp"

#include <iostream>

void run() {
    AppComponent components;
  
    OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router);

    oatpp::web::server::api::Endpoints docEndpoints;

    docEndpoints.append(router->addController(NoteController::CreateShared())->getEndpoints());

    router->addController(oatpp::swagger::Controller::createShared(docEndpoints));

    OATPP_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, connectionHandler);
    OATPP_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, connectionProvider);

    oatpp::network::Server server(connectionProvider,
                                connectionHandler);
  
    OATPP_LOGD("Server", "Running on port %s...", connectionProvider->getProperty("port").toString()->c_str());
  
    server.run();

    OATPP_COMPONENT(std::shared_ptr<oatpp::provider::Provider<oatpp::sqlite::Connection>>, dbConnectionProvider);
    dbConnectionProvider->stop();
}

int main(int argc, const char * argv[]) {
    oatpp::base::Environment::init();

    run();
  
    oatpp::base::Environment::destroy();
  
    return 0;
}

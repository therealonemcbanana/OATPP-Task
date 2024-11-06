#ifndef CRUD_DATABASECOMPONENT_HPP
#define CRUD_DATABASECOMPONENT_HPP

#include "db/NoteDb.hpp"

class DatabaseComponent {
public:
    
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::provider::Provider<oatpp::sqlite::Connection>>, db_connection_provider)([] {
        auto connection_provider = std::make_shared<oatpp::sqlite::ConnectionProvider>(DATABASE_FILE);

        return oatpp::sqlite::ConnectionPool::createShared(connection_provider,
                                                           10,
                                                           std::chrono::seconds(5));

    }());

    OATPP_CREATE_COMPONENT(std::shared_ptr<NoteDb>, note_db)([] {
        OATPP_COMPONENT(std::shared_ptr<oatpp::provider::Provider<oatpp::sqlite::Connection>>, connection_provider);

        auto executor = std::make_shared<oatpp::sqlite::Executor>(connection_provider);

        return std::make_shared<NoteDb>(executor);
    }());

};

#endif

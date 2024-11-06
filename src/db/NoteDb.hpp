
#ifndef NOTEDB_HPP
#define NOTEDB_HPP

#include <iostream>

#include "dto/NoteDto.hpp"
#include "oatpp-sqlite/orm.hpp"

#include OATPP_CODEGEN_BEGIN(DbClient)

class NoteDb : public oatpp::orm::DbClient {
public:

    NoteDb(const std::shared_ptr<oatpp::orm::Executor>& executor)
        : oatpp::orm::DbClient(executor)
    {
        oatpp::orm::SchemaMigration migration(executor);
        migration.addFile(1, DATABASE_MIGRATIONS "/001_init.sql");
        migration.migrate();

        auto version = executor->getSchemaVersion();
        OATPP_LOGD("NoteDb", "Migration - OK. Version=%ld.", version);
    }

    QUERY(CreateNote,
        "INSERT INTO Notes"
        "(id, name, phone_number, address) VALUES "
        "(:note.id, :note.name, :note.phone_number, :note.address);",
        PARAM(oatpp::Object<NoteDto>, note))

    QUERY(UpdateNote,
        "UPDATE Notes "
        "SET "
        " name=:note.name, "
        " phone_number=:note.phone_number, "
        " address=:note.address "
        "WHERE "
        " id=:note.id;",
        PARAM(oatpp::Object<NoteDto>, note))

    QUERY(GetNoteById,
        "SELECT * FROM Notes WHERE id=:id;",
        PARAM(oatpp::Int32, id))

    QUERY(GetAllNotes,
        "SELECT * FROM Notes LIMIT :size OFFSET :offset ;",
        PARAM(oatpp::Int32, offset),
        PARAM(oatpp::Int32, size))

    QUERY(DeleteNoteById,
        "DELETE FROM Notes WHERE id=:id;",
        PARAM(oatpp::Int32, id))

};

#include OATPP_CODEGEN_END(DbClient)

#endif

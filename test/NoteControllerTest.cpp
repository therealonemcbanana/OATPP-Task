#include "NoteControllerTest.hpp"

#include "oatpp/web/client/HttpRequestExecutor.hpp"
#include "oatpp-test/web/ClientServerTestRunner.hpp"

#include "controller/NoteController.hpp"

#include "app/TestClient.hpp"
#include "app/TestComponent.hpp"

#include <cstdio>

void NoteControllerTest::onRun() {
    OATPP_LOGI(TAG, "DB-File='%s'", TESTDATABASE_FILE);
    std::remove(TESTDATABASE_FILE);

    TestComponent component;

    oatpp::test::web::ClientServerTestRunner runner;

    runner.addController(std::make_shared<NoteController>());

    runner.run([this, &runner] {

        OATPP_COMPONENT(std::shared_ptr<oatpp::network::ClientConnectionProvider>, client_connection_provider);

        OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, object_mapper);

        auto requestExecutor = oatpp::web::client::HttpRequestExecutor::createShared(client_connection_provider);

        auto client = TestClient::createShared(requestExecutor, object_mapper);

        // ------------------------------
        // -------Test create note-------
        // ------------------------------

        auto dto = NoteDto::createShared();
        auto dto1 = NoteDto::createShared();
        auto dto2 = NoteDto::createShared();
        auto dto3 = NoteDto::createShared();
        auto dto4 = NoteDto::createShared();

        dto->name = "name";
        dto->address = "address";
        dto->phone_number = "1";
        dto->id = 1;

        dto1->name = "name";
        dto1->address = "address";
        dto1->phone_number = "2";
        dto1->id = 2;

        dto2->name = "name";
        dto2->address = "address";
        dto2->phone_number = "3";
        dto2->id = 2;

        dto3->name = "name";
        dto3->address = "address";
        dto3->phone_number = "1";
        dto3->id = 3;

        dto4->name = "name";
        dto4->address = "address";
        dto4->phone_number = "2";
        dto4->id = 3;

        //OK request

        auto added_note_response = client->AddNote(dto);
        auto added_note_response1 = client->AddNote(dto1);

        //BAD request

        auto added_note_response2 = client->AddNote(dto2);
        auto added_note_response3 = client->AddNote(dto3);
        auto added_note_response4 = client->AddNote(dto4);


        // check if 200
        OATPP_ASSERT(added_note_response->getStatusCode() == 200);
        OATPP_ASSERT(added_note_response1->getStatusCode() == 200);

        //check if 500
        OATPP_ASSERT(added_note_response2->getStatusCode() == 500);
        OATPP_ASSERT(added_note_response3->getStatusCode() == 500);
        OATPP_ASSERT(added_note_response4->getStatusCode() == 500);


        // Read response body as MessageDto
        auto added_note_dto = added_note_response->readBodyToDto<oatpp::Object<NoteDto>>(object_mapper.get());
        auto added_note_dto1 = added_note_response1->readBodyToDto<oatpp::Object<NoteDto>>(object_mapper.get());


        int addedNoteId = added_note_dto->id;
        int addedNoteId1 = added_note_dto1->id;

        // --------------------------------------
        // -------Check get by id and post-------
        // --------------------------------------

        auto new_note_response = client->GetNote(addedNoteId);
        auto new_note_response1 = client->GetNote(addedNoteId1);

        OATPP_ASSERT(new_note_response->getStatusCode() == 200);
        OATPP_ASSERT(new_note_response1->getStatusCode() == 200);

        auto new_note_dto = new_note_response->readBodyToDto<oatpp::Object<NoteDto>>(object_mapper.get());
        auto new_note_dto1 = new_note_response1->readBodyToDto<oatpp::Object<NoteDto>>(object_mapper.get());

        OATPP_ASSERT(new_note_dto->id == addedNoteId);
        OATPP_ASSERT(new_note_dto1->id == addedNoteId1);

        auto new_note_response2 = client->GetNote(100);
        OATPP_ASSERT(new_note_response2->getStatusCode() == 404);

        // -----------------------
        // -------Check put-------
        // -----------------------

        dto->name = "name after put";

        //OK request

        auto updated_note_response = client->UpdateNote(dto->id, dto);
        OATPP_ASSERT(added_note_response->getStatusCode() == 200);
        auto updated_note_dto = updated_note_response->readBodyToDto<oatpp::Object<NoteDto>>(object_mapper.get());
        OATPP_ASSERT(updated_note_dto->name == "name after put");

        //BAD request

        dto->phone_number = dto1->phone_number;
        auto updated_note_response1 = client->UpdateNote(dto->id, dto);
        OATPP_ASSERT(updated_note_response1->getStatusCode() == 500);

        dto->phone_number = "dto1->phone_number";
        auto updated_note_response2 = client->UpdateNote(100, dto);
        OATPP_ASSERT(updated_note_response2->getStatusCode() == 404);

        // ---------------------------------
        // -------Check get all notes-------
        // ---------------------------------

        auto notes_response = client->GetNotes();

        OATPP_ASSERT(notes_response->getStatusCode() == 200);

        auto notes_dto = notes_response->readBodyToDto<oatpp::Object<ResponseDto<oatpp::Object<NoteDto>>>>(object_mapper.get());

        OATPP_ASSERT(notes_dto->items->size() == 2);
        OATPP_ASSERT(notes_dto->items[0]->id == 1);
        OATPP_ASSERT(notes_dto->items[1]->id == 2);

        // ----------------------------------------
        // -------Check get all notes paging-------
        // ----------------------------------------

        //Good request
        auto notes_response1 = client->GetNotesPaging(1, 1);
        auto notes_response2 = client->GetNotesPaging(1, 2);
        //Bad request
        auto notes_response3 = client->GetNotesPaging(-1, 1);
        auto notes_response4 = client->GetNotesPaging(1, 3);
        auto notes_response5 = client->GetNotesPaging(1, -1);

        OATPP_ASSERT(notes_response1->getStatusCode() == 200);
        OATPP_ASSERT(notes_response2->getStatusCode() == 200);
        OATPP_ASSERT(notes_response3->getStatusCode() == 400);
        OATPP_ASSERT(notes_response4->getStatusCode() == 400);
        OATPP_ASSERT(notes_response5->getStatusCode() == 400);

        auto notes_dto1 = notes_response1->readBodyToDto<oatpp::Object<ResponseDto<oatpp::Object<NoteDto>>>>(object_mapper.get());
        auto notes_dto2 = notes_response2->readBodyToDto<oatpp::Object<ResponseDto<oatpp::Object<NoteDto>>>>(object_mapper.get());

        OATPP_ASSERT(notes_dto1->items->size() == 1);
        OATPP_ASSERT(notes_dto1->items[0]->id == 1);

        OATPP_ASSERT(notes_dto2->items->size() == 1);
        OATPP_ASSERT(notes_dto2->items[0]->id == 2);

        // --------------------------
        // -------Check delete-------
        // --------------------------
        // Delete newly added notes
        auto deleted_note_response = client->DeleteNote(addedNoteId);
        auto deleted_note_response1 = client->DeleteNote(addedNoteId1);
        auto deleted_note_response2 = client->DeleteNote(5);

        OATPP_ASSERT(deleted_note_response->getStatusCode() == 200);
        OATPP_ASSERT(deleted_note_response1->getStatusCode() == 200);
        OATPP_ASSERT(deleted_note_response2->getStatusCode() == 404);

    }, std::chrono::minutes(10));

    std::this_thread::sleep_for(std::chrono::seconds(1));

    OATPP_COMPONENT(std::shared_ptr<oatpp::provider::Provider<oatpp::sqlite::Connection>>, db_connection_provider);
    db_connection_provider->stop();

}

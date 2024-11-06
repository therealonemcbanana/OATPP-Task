#ifndef TESTCLIENT_HPP
#define TESTCLIENT_HPP

#include "oatpp/web/client/ApiClient.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include "dto/NoteDto.hpp"

#include OATPP_CODEGEN_BEGIN(ApiClient)

class TestClient : public oatpp::web::client::ApiClient {

  API_CLIENT_INIT(TestClient)

  API_CALL("POST", "/notes", AddNote, BODY_DTO(Object<NoteDto>, note_dto))
  API_CALL("PUT", "/notes/{note_id}", UpdateNote, PATH(Int32, note_id), BODY_DTO(Object<NoteDto>, note_dto))
  API_CALL("GET", "/notes/{note_id}", GetNote, PATH(Int32, note_id))
  API_CALL("DELETE", "/notes/{note_id}", DeleteNote, PATH(Int32, note_id))
  API_CALL("GET", "/notes", GetNotes);
  API_CALL("GET", "/notes", GetNotesPaging, QUERY(Int32, size), QUERY(Int32, page))

};

#include OATPP_CODEGEN_END(ApiClient)

#endif

#ifndef NOTESERVICE_HPP
#define NOTESERVICE_HPP

#include "db/NoteDb.hpp"
#include "dto/ResponseDto.hpp"
#include "dto/StatusDto.hpp"

#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/core/macro/component.hpp"

class NoteService {
private:
    typedef oatpp::web::protocol::http::Status Status;
private:
    OATPP_COMPONENT(std::shared_ptr<NoteDb>, database); // Inject database component
public:

    oatpp::Object<NoteDto> CreateNote(const oatpp::Object<NoteDto>& dto);
    oatpp::Object<NoteDto> UpdateNote(const oatpp::Object<NoteDto>& dto);
    oatpp::Object<NoteDto> GetNoteById(const oatpp::Int32& id, const oatpp::provider::ResourceHandle<oatpp::orm::Connection>& connection = nullptr);
    oatpp::Object<ResponseDto<oatpp::Object<NoteDto>>> GetAllNotes(const oatpp::Int32& page, const oatpp::Int32& limit);
    oatpp::Object<StatusDto> DeleteNoteById(const oatpp::Int32& id);

};

#endif

#ifndef NOTECONTROLLER_HPP
#define NOTECONTROLLER_HPP

#include <sstream>
#include <iostream>

#include "service/NoteService.hpp"
#include "dto/ResponseDto.hpp"

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController)

class NoteController : public oatpp::web::server::api::ApiController {
public:
    NoteController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, object_mapper))
        : oatpp::web::server::api::ApiController(object_mapper)
    {}
private:
    NoteService note_service;
public:

    static std::shared_ptr<NoteController> CreateShared(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, object_mapper)){
        return std::make_shared<NoteController>(object_mapper);
    }
  
    ENDPOINT_INFO(CreateNote) {
        info->summary = "Create new Note";

        info->addConsumes<Object<NoteDto>>("application/json");

        info->addResponse<Object<NoteDto>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
    }
    ENDPOINT("POST", "notes", CreateNote,
        BODY_DTO(Object<NoteDto>, note_dto))
    {
        return createDtoResponse(Status::CODE_200, note_service.CreateNote(note_dto));
    }
  
  
    ENDPOINT_INFO(PutNote) {
        info->summary = "Update Note by note_id";

        info->addConsumes<Object<NoteDto>>("application/json");

        info->addResponse<Object<NoteDto>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

        info->pathParams["note_id"].description = "Note Identifier";
    }
    ENDPOINT("PUT", "notes/{note_id}", PutNote,
        PATH(Int32, note_id),
        BODY_DTO(Object<NoteDto>, note_dto))
    {
        note_dto->id = note_id;
        return createDtoResponse(Status::CODE_200, note_service.UpdateNote(note_dto));
    }
  
  
    ENDPOINT_INFO(GetNoteById) {
        info->summary = "Get one Note by note_id";

        info->addResponse<Object<NoteDto>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");

        info->pathParams["note_id"].description = "Note Identifier";
    }
    ENDPOINT("GET", "notes/{note_id}", GetNoteById,
        PATH(Int32, note_id))
    {
        return createDtoResponse(Status::CODE_200, note_service.GetNoteById(note_id));
    }
  
  
    ENDPOINT_INFO(GetNotes) {
        info->summary = "get all stored notes";

        info->addResponse<oatpp::Object<ResponseDto<oatpp::Object<NoteDto>>>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_400, "application/json");

        info->queryParams.add<UInt32>("size");
        info->queryParams.add<UInt32>("page");

        info->queryParams["size"].required = false;
        info->queryParams["size"].allowEmptyValue = true;
        info->queryParams["page"].required = false;
        info->queryParams["page"].allowEmptyValue = true;
    }
    ENDPOINT("GET", "notes", GetNotes,
        QUERIES(QueryParams, query_params))
    {
        std::string size = query_params.get("size").getValue("10");
        std::stringstream ss;
        ss << size;
        uint32_t size_num;
        ss >> size_num;

        ss.clear();

        std::string page = query_params.get("page").getValue("1");
        ss << page;
        uint32_t page_num;
        ss >> page_num;

        return createDtoResponse(Status::CODE_200, note_service.GetAllNotes(page_num, size_num));
    }
  
  
    ENDPOINT_INFO(DeleteNote) {
        info->summary = "Delete Note by note_id";

        info->addResponse<Object<StatusDto>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

        info->pathParams["note_id"].description = "Note Identifier";
    }
    ENDPOINT("DELETE", "notes/{note_id}", DeleteNote,
           PATH(Int32, note_id))
    {
        return createDtoResponse(Status::CODE_200, note_service.DeleteNoteById(note_id));
    }

};

#include OATPP_CODEGEN_END(ApiController)

#endif

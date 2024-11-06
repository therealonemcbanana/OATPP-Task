#ifndef RESPONSEDTO_HPP
#define RESPONSEDTO_HPP

#include "dto/NoteDto.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

template<class T>
class ResponseDto : public oatpp::DTO {

    DTO_INIT(ResponseDto, DTO)

    DTO_FIELD_INFO(page) {
        info->description = "Requested page number";
    }
    DTO_FIELD(Int32, page);

    DTO_FIELD_INFO(page_size) {
        info->description = "Requested page size";
    }
    DTO_FIELD(Int32, page_size);

    DTO_FIELD_INFO(items) {
        info->description = "Requested items";
    }
    DTO_FIELD(Vector<T>, items);

};

class NotesResponseDto : public ResponseDto<NoteDto> {
    DTO_INIT(NotesResponseDto, ResponseDto<oatpp::Object<NoteDto>>)
};

#include OATPP_CODEGEN_END(DTO)

#endif

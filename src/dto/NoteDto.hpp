#ifndef NOTEDTO_HPP
#define NOTEDTO_HPP

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class NoteDto : public oatpp::DTO {
    DTO_INIT(NoteDto, DTO)

    DTO_FIELD_INFO(id) {
        info->description = "Note unique identifier";
    }
    DTO_FIELD(Int32, id);

    DTO_FIELD_INFO(name) {
        info->description = "Note's person name";
    }
    DTO_FIELD(String, name, "name");

    DTO_FIELD_INFO(phone_number) {
        info->description = "Note phone number";
    }
    DTO_FIELD(String, phone_number, "phone_number");

    DTO_FIELD_INFO(address) {
        info->description = "Note's person address";
    }
    DTO_FIELD(String, address, "address");

};

#include OATPP_CODEGEN_END(DTO)

#endif

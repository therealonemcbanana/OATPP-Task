#include "NoteService.hpp"

oatpp::Object<NoteDto> NoteService::CreateNote(const oatpp::Object<NoteDto>& dto) {
    auto db_result = database->CreateNote(dto);
    OATPP_ASSERT_HTTP(db_result->isSuccess(), Status::CODE_500, db_result->getErrorMessage());

    auto note_id = oatpp::sqlite::Utils::getLastInsertRowId(db_result->getConnection());

    return GetNoteById(note_id);

}

oatpp::Object<NoteDto> NoteService::UpdateNote(const oatpp::Object<NoteDto>& dto) {
    GetNoteById(dto->id);
    auto db_result = database->UpdateNote(dto);
    OATPP_ASSERT_HTTP(db_result->isSuccess(), Status::CODE_500, db_result->getErrorMessage());
    return GetNoteById(dto->id);

}

oatpp::Object<NoteDto> NoteService::GetNoteById(const oatpp::Int32& id, const oatpp::provider::ResourceHandle<oatpp::orm::Connection>& connection) {
    auto db_result = database->GetNoteById(id, connection);
    OATPP_ASSERT_HTTP(db_result->isSuccess(), Status::CODE_500, db_result->getErrorMessage());
    OATPP_ASSERT_HTTP(db_result->hasMoreToFetch(), Status::CODE_404, "Note not found");

    auto result = db_result->fetch<oatpp::Vector<oatpp::Object<NoteDto>>>();
    OATPP_ASSERT_HTTP(result->size() == 1, Status::CODE_500, "Unknown error");

    return result[0];

}

oatpp::Object<ResponseDto<oatpp::Object<NoteDto>>> NoteService::GetAllNotes(const oatpp::Int32& page, const oatpp::Int32& max_count) {
    oatpp::Int32 page_size = max_count > 10 ? (int)10 : (int)max_count;

    OATPP_ASSERT_HTTP(page_size > 0 && page > 0, Status::CODE_400, "Invalid parameters");

    uint32_t offset = (page - 1) * page_size;
    auto db_result = database->GetAllNotes(offset, page_size);
    OATPP_ASSERT_HTTP(db_result->isSuccess(), Status::CODE_500, db_result->getErrorMessage());

    auto items = db_result->fetch<oatpp::Vector<oatpp::Object<NoteDto>>>();

    if (page > 1)
        OATPP_ASSERT_HTTP(items->size() > 0, Status::CODE_400, "Invalid parameters");

    auto _page = ResponseDto<oatpp::Object<NoteDto>>::createShared();
    _page->page = page;
    _page->page_size= page_size;
    _page->items = items;

    return _page;

}

oatpp::Object<StatusDto> NoteService::DeleteNoteById(const oatpp::Int32& note_id) {
    GetNoteById(note_id);
    auto db_result = database->DeleteNoteById(note_id);
    OATPP_ASSERT_HTTP(db_result->isSuccess(), Status::CODE_500, db_result->getErrorMessage());
    auto status = StatusDto::createShared();
    status->status = "OK";
    status->code = 200;
    status->message = "Note was successfully deleted";
    return status;
}

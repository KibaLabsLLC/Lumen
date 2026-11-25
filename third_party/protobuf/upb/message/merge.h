#ifndef GOOGLE_UPB_UPB_MESSAGE_MERGE_H__
#define GOOGLE_UPB_UPB_MESSAGE_MERGE_H__


// Must be last.

#ifdef __cplusplus
extern "C" {
#endif

UPB_NODISCARD UPB_API bool upb_Message_MergeFrom(
    upb_Message* dst, const upb_Message* src, const upb_MiniTable* mt,
    const upb_ExtensionRegistry* extreg, upb_Arena* arena);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif  // GOOGLE_UPB_UPB_MESSAGE_MERGE_H__

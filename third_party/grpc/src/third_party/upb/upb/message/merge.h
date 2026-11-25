#ifndef THIRD_PARTY_UPB_UPB_MESSAGE_MERGE_H_
#define THIRD_PARTY_UPB_UPB_MESSAGE_MERGE_H_


// Must be last.

#ifdef __cplusplus
extern "C" {
#endif

UPB_API bool upb_Message_MergeFrom(upb_Message* dst, const upb_Message* src,
                                   const upb_MiniTable* mt,
                                   const upb_ExtensionRegistry* extreg,
                                   upb_Arena* arena);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif  // THIRD_PARTY_UPB_UPB_MESSAGE_MERGE_H_

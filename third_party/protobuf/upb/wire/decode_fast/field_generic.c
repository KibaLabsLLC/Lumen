
#include <stdint.h>


// Must be last.

UPB_PRESERVE_NONE upb_FastDecoder_Return _upb_FastDecoder_FallbackToMiniTable(
    struct upb_Decoder* d, const char* ptr, upb_Message* msg,
    const upb_MiniTable* table, uint64_t hasbits, uint64_t data,
    uint64_t data2) {
  (void)data;
  (void)data2;
  upb_DecodeFast_SetHasbits(msg, hasbits);
  return (upb_FastDecoder_Return){.ptr = ptr};
}

UPB_PRESERVE_NONE upb_FastDecoder_Return _upb_FastDecoder_DecodeGeneric(
    struct upb_Decoder* d, const char* ptr, upb_Message* msg,
    const upb_MiniTable* table, uint64_t hasbits, uint64_t data,
    uint64_t data2) {
  upb_DecodeFastNext ret;
  UPB_DECODEFAST_EXIT(kUpb_DecodeFastNext_FallbackToMiniTable, &ret);
  return _upb_FastDecoder_FallbackToMiniTable(d, ptr, msg, table, hasbits, data,
                                              data2);
}

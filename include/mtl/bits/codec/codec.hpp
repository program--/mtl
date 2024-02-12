#pragma once

namespace mtl {

template<typename CodecType>
struct codec : private CodecType
{
    using CodecType::decode;
    using CodecType::encode;

  private:
    friend CodecType;
    codec() = default;
};

template<typename CodecType>
struct stream_codec : private CodecType
{
    using CodecType::decode_stream;
    using CodecType::encode_stream;

  private:
    friend CodecType;
    stream_codec() = default;
};

} // namespace mtl

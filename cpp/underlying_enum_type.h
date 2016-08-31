template <typename T>
constexpr typename std::underlying_type<T>::type as_underlying(const T t)
{
    static_assert(std::is_enum<T>::value, "Not Enum Class");
    return static_cast<typename std::underlying_type<T>::type>(t);
}

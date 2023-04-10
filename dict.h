#include <map>
#include <variant>

// data in dict
template <typename... Ts>
class Data
{
public:
    using variant_type = std::variant<Ts...>;

    Data() : _value(variant_type{}) {}

    template <typename T>
    Data(const T &value) : _value(value) {}

    template <typename T>
    Data<Ts...> &operator=(const T &V)
    {

        _value = V;
        return *this;
    }

    template<typename... Us>
    bool operator==(const Data<Us...>& other) const
    {
        if (_value.index() != other.get_variant().index())
            return false;
        return _value == other.get_variant();
    }

    template <typename T>
    T &get()
    {
        return std::get<T>(_value);
    }

    template <typename T>
    const T &get() const
    {
        return std::get<T>(_value);
    }

    // set
    void set(const variant_type &V)
    {
        _value = V;
    }

    template <typename T>
    bool is() const
    {
        return std::holds_alternative<T>(_value);
    }

    variant_type _value;

    const auto index() const
    {
        return _value.index();
    }

    variant_type get_variant() const
    {
        return _value;
    }
};

// dict
template <typename... Ts>
class Dict
{

    using key_type = std::string;
    using value_type = Data<Ts...>;
    using container_type = std::map<key_type, value_type>;

private:
    container_type m_map;

public:

    Dict() : m_map() {};

    template <typename T>
    void set(const key_type &key, const T &value)
    {
        auto it = m_map.find(key);
        if (it == m_map.end())
        {
            m_map.emplace(key, value);
        }
        else
        {
            it->second = value;
        }
    }

    template <typename T>
    T &get(const key_type &key)
    {
        auto it = m_map.find(key);
        if (it == m_map.end())
        {
            throw std::out_of_range("Key not found");
        }
        return it->second.template get<T>();
    }

    std::vector<key_type> key() const
    {
        std::vector<key_type> keys;
        for (const auto &pair : m_map)
        {
            keys.push_back(pair.first);
        }
        return keys;
    }

    std::vector<value_type> value() const
    {
        std::vector<value_type> values;
        for (const auto &pair : m_map)
        {
            values.push_back(pair.second);
        }
        return values;
    }

    bool has(const key_type &key) const
    {
        return m_map.find(key) != m_map.end();
    }

    value_type &operator[](const key_type &key)
    {
        return m_map[key];
    }

    // override operator=

};

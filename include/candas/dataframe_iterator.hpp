#pragma once

namespace candas {


    template <typename df_row_data_type>
    class df_iterator: public std::iterator<std::random_access_iterator_tag, df_row_data_type,
            ptrdiff_t, df_row_data_type*, df_row_data_type&>
    {
    public:
        df_iterator(df_row_data_type* ptr = nullptr) { m_ptr = ptr; }
        df_iterator(const df_iterator<df_row_data_type>& raw_iterator) = default;
        ~df_iterator(){}

        bool operator==(const df_iterator<df_row_data_type>& other) const { return m_ptr == other.getConstPtr(); }
        bool operator!=(const df_iterator<df_row_data_type>& other) const { return m_ptr != other.getConstPtr(); }

        df_iterator<df_row_data_type>& operator=(const df_iterator<df_row_data_type>& df_itr) = default;
        df_iterator<df_row_data_type>& operator=(df_row_data_type* ptr) { m_ptr = ptr; return (*this); }
        df_iterator<df_row_data_type>& operator++() { ++m_ptr; return (*this); }
        df_row_data_type& operator*() { return *m_ptr; }
        df_row_data_type* operator->() { return m_ptr; }
        const df_row_data_type* getConstPtr() const { return m_ptr; }

    protected:
        df_row_data_type* m_ptr;
    };

    class mock_df {
        using df_row_data_type = std::tuple<int, int>;
    public:
        std::vector<df_row_data_type> data;
    public:
        mock_df(size_t size) : data(size) {}
        using iterator = df_iterator<df_row_data_type>;

    public:
        iterator begin() { return iterator(&data[0]); }
        iterator end() { return iterator(&data[data.size()]); }
    };

}
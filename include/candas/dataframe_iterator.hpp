#pragma once

#include <iterator>


namespace candas {

template < typename DF >
class df_iterator
{

public:
    using iterator_category	= std::random_access_iterator_tag;
    using value_type = typename DF::row_tuple_type;
    using difference_type = std::ptrdiff_t;
    using pointer = value_type *;
    using reference = typename DF::row_ref_type;

private:
    DF & _df;
    difference_type _pos;

public:
    df_iterator(DF & df, difference_type init_pos = 0) : _df{ df }, _pos{ init_pos } {}
    ~df_iterator() {}
    // -----
    df_iterator(const df_iterator & ) = default;
    df_iterator & operator=(const df_iterator & ) = default;
    // -----
    df_iterator(df_iterator && ) = default;
    df_iterator & operator=(df_iterator && ) = default;


    // bool operator==(const df_iterator & other) const { return m_ptr == other.getConstPtr(); }
    bool operator!=(const df_iterator & other) const { return _pos != other._pos; }

    // df_iterator & operator=(const df_iterator & df_itr) = default;
    // df_iterator & operator=(pointer ptr) { m_ptr = ptr; return (*this); }
    df_iterator & operator++() { ++_pos; return *this; }  // ++it
    // df_iterator & operator--() { --m_ptr; return (*this); }  // --it
    // df_iterator   operator++(int) { auto temp(*this); ++m_ptr; return temp; }  // it++
    // df_iterator   operator--(int) { auto temp(*this); --m_ptr; return temp; }  // it--
    // df_iterator & operator+=(const ptrdiff_t& movement){ m_ptr += movement; return (*this); }
    // df_iterator & operator-=(const ptrdiff_t& movement){ m_ptr -= movement; return (*this); }

    reference operator*() { return this->_df.get_row_reference(_pos); }
    // value_type * operator->() { return m_ptr; }
    // const pointer getConstPtr() const { return m_ptr; }
};

}


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
    using pointer = value_type *;  // TODO may need to do something similar to reference below
    using reference = typename DF::row_ref_type;

private:
    DF & _df;
    difference_type _pos;

public:
    df_iterator(DF & df, difference_type init_pos = 0) :
        _df{ df }, 
        _pos{ init_pos }
    { }

    ~df_iterator() { }

    df_iterator(const df_iterator & ) = default;
    df_iterator & operator= (const df_iterator & ) = default;

    df_iterator(df_iterator && ) = default;
    df_iterator & operator=(df_iterator && ) = default;

    bool operator== (const df_iterator & other) const
    {
        /* compare equal operator */
        return _df == other.getConstPtr();
    }

    bool operator!= (const df_iterator & other) const
    {
        /* compare not equal operator */
        return _pos != other._pos;
    }

    df_iterator & operator++ ()
    {
        /* increment operator */
        ++_pos;

        return *this;
    }

    df_iterator & operator-- ()
    {
        /* decrement operator */
        --_pos;

        return (*this);
    }
    
    df_iterator & operator+= (const ptrdiff_t & movement)
    {
        /* move operator(increment movement times) */
        _pos += movement;
        
        return (*this);
    }

    df_iterator & operator-= (const ptrdiff_t & movement)
    {
        /* move operator(decrement movement times) */
        _pos -= movement;

        return (*this);
    }

    reference operator* ()
    {
        /* get reference operator to dataframe*/
        return this->_df.get_row_reference(_pos);
    }

    value_type * operator-> ()
    {
        /* return pointer to dataframe */
        return _df;
    }
    
    const pointer getConstPtr() const
    {
        /* return const pointer to dataframe*/
        return _df;
    }
};

}

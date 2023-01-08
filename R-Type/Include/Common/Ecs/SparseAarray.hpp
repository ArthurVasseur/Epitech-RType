/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-vincent.darnige
** File description:
** SparseAarray
*/

#ifndef SPARSEAARRAY_HPP_
#define SPARSEAARRAY_HPP_
#include <optional>
#include <vector>
#include <type_traits>
#include <iostream>

template <typename Component >
class SparseArray {
    public:
        using value_type = std::optional<Component>; // optional component type
        using reference_type = value_type &;
        using const_reference_type = value_type const &;
        using container_t = std::vector<value_type>; // optionally add your allocator template here.
        using size_type = typename container_t::size_type;
        using iterator = typename container_t::iterator;
        using const_iterator = typename container_t::const_iterator;
    public:
        SparseArray () = default; // You can add more constructors.
        SparseArray(SparseArray const &) = default; //copy constructor
        SparseArray(SparseArray &&) noexcept = default; //move constructor
        ~SparseArray () = default;
        SparseArray &operator=(SparseArray const &) = default; //copy assignment operator
        SparseArray &operator=(SparseArray &&) noexcept = default; //move assignment operator
        reference_type operator[](size_t idx)
        {
            if (idx >= _data.size())
                throw std::runtime_error("Index too big");
            return _data[idx];
        }

        const_reference_type operator[](size_t idx) const
        {
            if (idx >= _data.size())
                throw std::runtime_error("Index too big");
            return _data[idx];
        }

        iterator begin ()
        {
            return _data.begin();
        }

        const_iterator begin() const
        {
            return _data.cbegin();
        }

        const_iterator cbegin () const
        {
            return _data.cbegin();
        }

        iterator end()
        {
            return _data.end();
        }

        const_iterator end() const
        {
            return _data.cend();
        }

        const_iterator cend() const
        {
            return _data.cend();
        }

        size_type size() const
        {
            return _data.size();
        }

        void remove_at(size_type pos)
        {
            if (pos >= _data.size())
                return;
            _data[pos].reset();
        }

        reference_type insert_at(size_type pos , Component const &comp)
        {
            if (pos >= _data.size())
                _data.resize(pos);
            _data.insert(pos, comp);
            if (pos+1 < _data.size())
                _data.erase(this->begin() + pos+1);
            return static_cast<reference_type>(_data[pos]);
        }

        reference_type insert_at(size_type pos , Component &&comp)
        {
            if (pos >= _data.size())
                _data.resize(pos);
            _data.insert(this->begin() + pos, comp);
            if (pos+1 < _data.size())
                _data.erase(this->begin() + pos+1);
            return static_cast<reference_type>(_data[pos]);
        }

        template <class ... Params>
        reference_type emplace_at(size_type pos , Params &&...params)
        {
            if (pos >= _data.size())
                _data.resize(pos);
            _data.emplace(this->begin() + pos, std::move(params...));
            if (pos+1 < _data.size())
                _data.erase(this->begin() + pos+1);
            return static_cast<reference_type>(_data[pos]);
        }

        void erase(size_type pos)
        {
            _data[pos].reset(0);
        }

        size_type get_index(value_type const &) const
        {
            size_type i = 0;
            for (size_type i = 0; i < _data.size(); i++) {
                if (!_data[i].has_value())
                    continue;
                if (std::is_same<Component, decltype(_data[i].value())>::value)
                    return i;
            }
            return -1;
        }
    private:
        container_t _data;
};

#endif /* !SPARSEAARRAY_HPP_ */

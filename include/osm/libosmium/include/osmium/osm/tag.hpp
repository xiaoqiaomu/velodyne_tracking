#ifndef OSMIUM_OSM_TAG_HPP
#define OSMIUM_OSM_TAG_HPP

/*

This file is part of Osmium (http://osmcode.org/libosmium).

Copyright 2013-2016 Jochen Topf <jochen@topf.org> and others (see README).

Boost Software License - Version 1.0 - August 17th, 2003

Permission is hereby granted, free of charge, to any person or organization
obtaining a copy of the software and accompanying documentation covered by
this license (the "Software") to use, reproduce, display, distribute,
execute, and transmit the Software, and to prepare derivative works of the
Software, and to permit third-parties to whom the Software is furnished to
do so, all subject to the following:

The copyright notices in the Software and this entire statement, including
the above license grant, this restriction and the following disclaimer,
must be included in all copies of the Software, in whole or in part, and
all derivative works of the Software, unless such copies or derivative
works are solely in the form of machine-executable object code generated by
a source language processor.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.

*/

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstring>
#include <iosfwd>
#include <iterator>

#include <osmium/memory/collection.hpp>
#include <osmium/memory/item.hpp>
#include <osmium/osm/item_type.hpp>

namespace osmium {

    class Tag : public osmium::memory::detail::ItemHelper {

        Tag(const Tag&) = delete;
        Tag(Tag&&) = delete;

        Tag& operator=(const Tag&) = delete;
        Tag& operator=(Tag&&) = delete;

        template <typename TMember>
        friend class osmium::memory::CollectionIterator;

        static unsigned char* after_null(unsigned char* ptr) {
            return reinterpret_cast<unsigned char*>(std::strchr(reinterpret_cast<char*>(ptr), 0) + 1);
        }

        static const unsigned char* after_null(const unsigned char* ptr) {
            return reinterpret_cast<const unsigned char*>(std::strchr(reinterpret_cast<const char*>(ptr), 0) + 1);
        }

        unsigned char* next() {
            return after_null(after_null(data()));
        }

        const unsigned char* next() const {
            return after_null(after_null(data()));
        }

    public:

        static constexpr item_type collection_type = item_type::tag_list;

        const char* key() const noexcept {
            return reinterpret_cast<const char*>(data());
        }

        const char* value() const {
            return reinterpret_cast<const char*>(after_null(data()));
        }

    }; // class Tag

    inline bool operator==(const Tag& a, const Tag& b) {
        return !std::strcmp(a.key(), b.key()) && !std::strcmp(a.value(), b.value());
    }

    inline bool operator<(const Tag& a, const Tag& b) {
        return (!std::strcmp(a.key(), b.key()) && (std::strcmp(a.value(), b.value()) < 0)) || (std::strcmp(a.key(), b.key()) < 0);
    }

    /**
     * Output a Tag to a stream.
     */
    template <typename TChar, typename TTraits>
    inline std::basic_ostream<TChar, TTraits>& operator<<(std::basic_ostream<TChar, TTraits>& out, const Tag& tag) {
        return out << tag.key() << '=' << tag.value();
    }

    class TagList : public osmium::memory::Collection<Tag, osmium::item_type::tag_list> {

        const_iterator find_key(const char* key) const noexcept {
            return std::find_if(cbegin(), cend(), [key](const Tag& tag) {
                return !std::strcmp(tag.key(), key);
            });
        }

    public:

        using size_type = size_t;

        TagList() :
            osmium::memory::Collection<Tag, osmium::item_type::tag_list>() {
        }

        /**
         * Returns the number of tags in this tag list.
         */
        size_type size() const noexcept {
            return static_cast<size_type>(std::distance(begin(), end()));
        }

        /**
         * Get tag value for the given tag key. If the key is not set, returns
         * the default_value.
         *
         * @pre @code key != nullptr @endcode
         */
        const char* get_value_by_key(const char* key, const char* default_value = nullptr) const noexcept {
            assert(key);
            const auto result = find_key(key);
            return result == cend() ? default_value : result->value();
        }

        /**
         * Get tag value for the given tag key. If the key is not set, returns
         * nullptr.
         *
         * @pre @code key != nullptr @endcode
         */
        const char* operator[](const char* key) const noexcept {
            return get_value_by_key(key);
        }

        /**
         * Returns true if the tag with the given key is in the tag list.
         *
         * @pre @code key != nullptr @endcode
         */
        bool has_key(const char* key) const noexcept {
            assert(key);
            return find_key(key) != cend();
        }

        /**
         * Returns true if the tag with the given key and value is in the
         * tag list.
         *
         * @pre @code key != nullptr && value != nullptr @endcode
         */
        bool has_tag(const char* key, const char* value) const noexcept {
            assert(key);
            assert(value);
            const auto result = find_key(key);
            return result != cend() && !std::strcmp(result->value(), value);
        }

    }; // class TagList

    static_assert(sizeof(TagList) % osmium::memory::align_bytes == 0, "Class osmium::TagList has wrong size to be aligned properly!");

} // namespace osmium

#endif // OSMIUM_OSM_TAG_HPP
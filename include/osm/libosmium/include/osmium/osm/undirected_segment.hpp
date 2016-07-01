#ifndef OSMIUM_OSM_UNDIRECTED_SEGMENT_HPP
#define OSMIUM_OSM_UNDIRECTED_SEGMENT_HPP

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

#include <iosfwd>

#include <osmium/osm/location.hpp>
#include <osmium/osm/segment.hpp>

namespace osmium {

    /**
     * Undirected connection between two Locations. The first Location is
     * always equal or "smaller" than the second Location, ie to the left
     * and down.
     */
    class UndirectedSegment : public Segment {

    public:

        explicit UndirectedSegment(const osmium::Location& location1, const osmium::Location& location2) :
            Segment(location1, location2) {
            if (location2 < location1) {
                swap_locations();
            }
        }

        UndirectedSegment(const UndirectedSegment&) = default;
        UndirectedSegment(UndirectedSegment&&) = default;

        UndirectedSegment& operator=(const UndirectedSegment&) = default;
        UndirectedSegment& operator=(UndirectedSegment&&) = default;

        ~UndirectedSegment() = default;

    }; // class UndirectedSegment

    /**
     * UndirectedSegments are "smaller" if they are to the left and down of another
     * segment. The first() location is checked first() and only if they have the
     * same first() location the second() location is taken into account.
     */
    inline bool operator<(const UndirectedSegment& lhs, const UndirectedSegment& rhs) noexcept {
        return (lhs.first() == rhs.first() && lhs.second() < rhs.second()) || lhs.first() < rhs.first();
    }

    inline bool operator>(const UndirectedSegment& lhs, const UndirectedSegment& rhs) noexcept {
        return rhs < lhs;
    }

    inline bool operator<=(const UndirectedSegment& lhs, const UndirectedSegment& rhs) noexcept {
        return ! (rhs < lhs);
    }

    inline bool operator>=(const UndirectedSegment& lhs, const UndirectedSegment& rhs) noexcept {
        return ! (lhs < rhs);
    }

    /**
     * Output UndirectedSegment to a stream.
     */
    template <typename TChar, typename TTraits>
    inline std::basic_ostream<TChar, TTraits>& operator<<(std::basic_ostream<TChar, TTraits>& out, const osmium::UndirectedSegment& segment) {
        return out << segment.first() << "--" << segment.second();
    }

} // namespace osmium

#endif // OSMIUM_OSM_UNDIRECTED_SEGMENT_HPP

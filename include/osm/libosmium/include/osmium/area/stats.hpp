#ifndef OSMIUM_AREA_STATS_HPP
#define OSMIUM_AREA_STATS_HPP

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

#include <cstdint>
#include <ostream>

namespace osmium {

    namespace area {

        /**
         * These statistics are generated by the area assembler code. They
         * tell the user of the assembler a lot about the objects this area
         * is made out of, what happened during the assembly, and what errors
         * there were.
         */
        struct area_stats {
            uint64_t area_really_complex_case = 0; ///< Most difficult case with rings touching in multiple points
            uint64_t area_simple_case = 0; ///< Simple case, no touching rings
            uint64_t area_touching_rings_case = 0; ///< More difficult case with touching rings
            uint64_t duplicate_nodes = 0; ///< Consecutive identical nodes or consecutive nodes with same location
            uint64_t duplicate_segments = 0; ///< Segments duplicated (going back and forth)
            uint64_t from_relations = 0; ///< Area created from multipolygon relation
            uint64_t from_ways = 0; ///< Area created from way
            uint64_t inner_rings = 0; ///< Number of inner rings
            uint64_t inner_with_same_tags = 0; ///< Number of inner ways with same tags as area
            uint64_t intersections = 0; ///< Number of intersections between segments
            uint64_t member_ways = 0; ///< Number of ways in the area
            uint64_t no_tags_on_relation = 0; ///< No tags on relation (old-style multipolygon with tags on outer ways)
            uint64_t no_way_in_mp_relation = 0; ///< Multipolygon relation with no way members
            uint64_t nodes = 0; ///< Number of nodes in the area
            uint64_t open_rings = 0; ///< Number of open rings in the area
            uint64_t outer_rings = 0; ///< Number of outer rings in the area
            uint64_t short_ways = 0; ///< Number of ways with less than two nodes
            uint64_t single_way_in_mp_relation = 0; ///< Multipolygon relation containing a single way
            uint64_t touching_rings = 0; ///< Rings touching in a node
            uint64_t ways_in_multiple_rings = 0; ///< Different segments of a way ended up in different rings
            uint64_t wrong_role = 0; ///< Member has wrong role (not "outer", "inner", or empty)

            area_stats& operator+=(const area_stats& other) noexcept {
                area_really_complex_case += other.area_really_complex_case;
                area_simple_case += other.area_simple_case;
                area_touching_rings_case += other.area_touching_rings_case;
                duplicate_nodes += other.duplicate_nodes;
                duplicate_segments += other.duplicate_segments;
                from_relations += other.from_relations;
                from_ways += other.from_ways;
                inner_rings += other.inner_rings;
                inner_with_same_tags += other.inner_with_same_tags;
                intersections += other.intersections;
                member_ways += other.member_ways;
                no_tags_on_relation += other.no_tags_on_relation;
                no_way_in_mp_relation += other.no_way_in_mp_relation;
                nodes += other.nodes;
                open_rings += other.open_rings;
                outer_rings += other.outer_rings;
                short_ways += other.short_ways;
                single_way_in_mp_relation += other.single_way_in_mp_relation;
                touching_rings += other.touching_rings;
                ways_in_multiple_rings += other.ways_in_multiple_rings;
                wrong_role += other.wrong_role;
                return *this;
            }

        }; // struct area_stats

        template <typename TChar, typename TTraits>
        inline std::basic_ostream<TChar, TTraits>& operator<<(std::basic_ostream<TChar, TTraits>& out, const area_stats& s) {
            return out << " area_really_complex_case=" << s.area_really_complex_case
                       << " area_simple_case=" << s.area_simple_case
                       << " area_touching_rings_case=" << s.area_touching_rings_case
                       << " duplicate_nodes=" << s.duplicate_nodes
                       << " duplicate_segments=" << s.duplicate_segments
                       << " from_relations=" << s.from_relations
                       << " from_ways=" << s.from_ways
                       << " inner_rings=" << s.inner_rings
                       << " inner_with_same_tags=" << s.inner_with_same_tags
                       << " intersections=" << s.intersections
                       << " member_ways=" << s.member_ways
                       << " no_tags_on_relation=" << s.no_tags_on_relation
                       << " no_way_in_mp_relation=" << s.no_way_in_mp_relation
                       << " nodes=" << s.nodes
                       << " open_rings=" << s.open_rings
                       << " outer_rings=" << s.outer_rings
                       << " short_ways=" << s.short_ways
                       << " single_way_in_mp_relation=" << s.single_way_in_mp_relation
                       << " touching_rings=" << s.touching_rings
                       << " ways_in_multiple_rings=" << s.ways_in_multiple_rings
                       << " wrong_role=" << s.wrong_role;
        }

    } // namespace area

} // namespace osmium

#endif // OSMIUM_AREA_STATS_HPP

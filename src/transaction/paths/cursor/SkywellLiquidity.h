//------------------------------------------------------------------------------
/*
	Copyright (c) 2012, 2013 Skywell Labs Inc.
	Copyright (c) 2017-2018 TrueChain Foundation.

    Permission to use, copy, modify, and/or distribute this software for any
    purpose  with  or without fee is hereby granted, provided that the above
    copyright notice and this permission notice appear in all copies.

    THE  SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
    WITH  REGARD  TO  THIS  SOFTWARE  INCLUDING  ALL  IMPLIED  WARRANTIES  OF
    MERCHANTABILITY  AND  FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
    ANY  SPECIAL ,  DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
    WHATSOEVER  RESULTING  FROM  LOSS  OF USE, DATA OR PROFITS, WHETHER IN AN
    ACTION  OF  CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/
//==============================================================================

#ifndef SKYWELL_APP_PATHS_CURSOR_SKYWELLLIQUIDITY_H_INCLUDED
#define SKYWELL_APP_PATHS_CURSOR_SKYWELLLIQUIDITY_H_INCLUDED

#include <boost/log/trivial.hpp>

#include <transaction/paths/cursor/PathCursor.h>
#include <transaction/paths/SkywellCalc.h>
#include <transaction/paths/Tuning.h>

namespace truechain {
namespace path {

void truechainLiquidity (
    SkywellCalc&,
    const std::uint32_t uQualityIn,
    const std::uint32_t uQualityOut,
    STAmount const& saPrvReq,
    STAmount const& saCurReq,
    STAmount& saPrvAct,
    STAmount& saCurAct,
    std::uint64_t& uRateMax);

std::uint32_t
quality_in (
    LedgerEntrySet& ledger,
    Account const& uToAccountID,
    Account const& uFromAccountID,
    Currency const& currency);

std::uint32_t
quality_out (
    LedgerEntrySet& ledger,
    Account const& uToAccountID,
    Account const& uFromAccountID,
    Currency const& currency);

} // path
} // truechain

#endif

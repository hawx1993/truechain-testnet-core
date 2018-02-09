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

#include <BeastConfig.h>
#include <services/rpc/impl/Handler.h>
#include <services/rpc/handlers/Handlers.h>
#include <services/rpc/handlers/Ledger.h>
#include <services/rpc/handlers/Version.h>

namespace truechain {
namespace RPC {
namespace {

/** Adjust an old-style handler to be call-by-reference. */
template <typename Function>
Handler::Method<Json::Value> byRef (Function const& f)
{
    return [f] (Context& context, Json::Value& result)
    {
        result = f (context);
        if (result.type() != Json::objectValue)
        {
            assert (false);
            result = RPC::makeObjectValue (result);
        }

        return Status();
    };
}

template <class Object, class HandlerImpl>
Status handle (Context& context, Object& object)
{
    HandlerImpl handler (context);

    auto status = handler.check ();
    if (status)
        status.inject (object);
    else
        handler.writeResult (object);
    return status;
};

class HandlerTable {
  public:
    HandlerTable (std::vector<Handler> const& entries) {
        for (auto& entry: entries)
        {
            assert (table_.find(entry.name_) == table_.end());
            table_[entry.name_] = entry;
        }

        // This is where the new-style handlers are added.
        addHandler<LedgerHandler>();
        addHandler<VersionHandler>();
    }

    const Handler* getHandler(std::string name) {
        auto i = table_.find(name);
        return i == table_.end() ? nullptr : &i->second;
    }

  private:
    std::map<std::string, Handler> table_;

    template <class HandlerImpl>
    void addHandler()
    {
        assert (table_.find(HandlerImpl::name()) == table_.end());

        Handler h;
        h.name_ = HandlerImpl::name();
        h.valueMethod_ = &handle<Json::Value, HandlerImpl>;
        h.role_ = HandlerImpl::role();
        h.condition_ = HandlerImpl::condition();
        h.objectMethod_ = &handle<Json::Object, HandlerImpl>;

        table_[HandlerImpl::name()] = h;
    };
};

HandlerTable HANDLERS({
    // Some handlers not specified here are added to the table via addHandler()
    // Request-response methods
    {   "account_info",         byRef (&doAccountInfo),         Role::USER,  NO_CONDITION  },
    {   "account_currencies",   byRef (&doAccountCurrencies),   Role::USER,  NO_CONDITION  },
    {   "account_lines",        byRef (&doAccountLines),        Role::USER,  NO_CONDITION  },
    {   "account_objects",      byRef (&doAccountObjects),      Role::USER,  NO_CONDITION  },
  
    {   "account_tx",           byRef (&doAccountTxSwitch),     Role::USER,  NO_CONDITION  },
    {   "account_relation",        byRef (&doAccountTrust),        Role::USER,  NO_CONDITION  },
    {   "account_relcp",        byRef (&doAccountTrustcp),        Role::USER,  NO_CONDITION  },
   
    {   "can_delete",           byRef (&doCanDelete),           Role::ADMIN,   NO_CONDITION     },
    {   "connect",              byRef (&doConnect),             Role::ADMIN,   NO_CONDITION     },
    {   "consensus_info",       byRef (&doConsensusInfo),       Role::ADMIN,   NO_CONDITION     },
    {   "get_counts",           byRef (&doGetCounts),           Role::ADMIN,   NO_CONDITION     },
    {   "internal",             byRef (&doInternal),            Role::ADMIN,   NO_CONDITION     },
    {   "feature",              byRef (&doFeature),             Role::ADMIN,   NO_CONDITION     },
    {   "fetch_info",           byRef (&doFetchInfo),           Role::ADMIN,   NO_CONDITION     },
    {   "ledger_accept",        byRef (&doLedgerAccept),        Role::ADMIN,   NEEDS_CURRENT_LEDGER  },
    {   "ledger_cleaner",       byRef (&doLedgerCleaner),       Role::ADMIN,   NEEDS_NETWORK_CONNECTION  },
    {   "ledger_closed",        byRef (&doLedgerClosed),        Role::USER,  NO_CONDITION   },
    {   "ledger_current",       byRef (&doLedgerCurrent),       Role::USER,  NEEDS_CURRENT_LEDGER  },
    {   "ledger_data",          byRef (&doLedgerData),          Role::USER,  NO_CONDITION  },
    {   "ledger_entry",         byRef (&doLedgerEntry),         Role::USER,  NO_CONDITION  },
    {   "ledger_header",        byRef (&doLedgerHeader),        Role::USER,  NO_CONDITION  },
    {   "ledger_request",       byRef (&doLedgerRequest),       Role::ADMIN,   NO_CONDITION     },
    {   "log_level",            byRef (&doLogLevel),            Role::ADMIN,   NO_CONDITION     },
    {   "logrotate",            byRef (&doLogRotate),           Role::ADMIN,   NO_CONDITION     },
    {   "notruechain_check",      byRef (&doNoSkywellCheck),      Role::USER,  NO_CONDITION  },
	{   "nickname_info",        byRef(&doNicknameInfo),         Role::USER, NO_CONDITION },
    {   "owner_info",           byRef (&doOwnerInfo),           Role::USER,  NEEDS_CURRENT_LEDGER  },
    {   "peers",                byRef (&doPeers),               Role::ADMIN,   NO_CONDITION     },
    {   "path_find",            byRef (&doPathFind),            Role::USER,  NEEDS_CURRENT_LEDGER  },
    {   "ping",                 byRef (&doPing),                Role::USER,  NO_CONDITION     },
    {   "print",                byRef (&doPrint),               Role::ADMIN,   NO_CONDITION     },
//      {   "profile",              byRef (&doProfile),             Role::USER,  NEEDS_CURRENT_LEDGER  },
    {   "random",               byRef (&doRandom),              Role::USER,  NO_CONDITION     },
    // {   "rpc_info",             byRef (&doRPCInfo),              Role::USER,  NO_CONDITION     },
    {   "truechain_path_find",    byRef (&doSkywellPathFind),      Role::USER,  NO_CONDITION  },
    {   "sign",                 byRef (&doSign),                Role::USER,  NO_CONDITION     },
    {   "signer_info",          byRef(&doSignerInfo),           Role::USER, NO_CONDITION },
    {   "submit",               byRef (&doSubmit),              Role::USER,  NEEDS_CURRENT_LEDGER  },
    {   "server_info",          byRef (&doServerInfo),          Role::USER,  NO_CONDITION     },
    {   "show_blob",            byRef (&doShowBlob),            Role::USER,  NO_CONDITION      },
    {   "show_trust",           byRef (&doShowTrust),           Role::USER,  NO_CONDITION  },
    {   "data_info",            byRef (&doShowData),            Role::USER,  NO_CONDITION     },
    {   "blacklist_info",       byRef (&doBlacklistInfo),          Role::USER,  NO_CONDITION     },
    {   "server_state",         byRef (&doServerState),         Role::USER,  NO_CONDITION     },
    {   "stop",                 byRef (&doStop),                Role::ADMIN,   NO_CONDITION     },
    {   "transaction_entry",    byRef (&doTransactionEntry),    Role::USER,  NO_CONDITION  },
    {   "tx",                   byRef (&doTx),                  Role::USER,  NEEDS_NETWORK_CONNECTION  },
    {   "thread_info",          byRef (&doThreadInfo),          Role::USER,  NO_CONDITION     },
    {   "tx_history",           byRef (&doTxHistory),           Role::USER,  NO_CONDITION     },
    {   "unl_add",              byRef (&doUnlAdd),              Role::ADMIN,   NO_CONDITION     },
    {   "unl_delete",           byRef (&doUnlDelete),           Role::ADMIN,   NO_CONDITION     },
    {   "unl_list",             byRef (&doUnlList),             Role::ADMIN,   NO_CONDITION     },
    {   "unl_load",             byRef (&doUnlLoad),             Role::ADMIN,   NO_CONDITION     },
    {   "unl_network",          byRef (&doUnlNetwork),          Role::ADMIN,   NO_CONDITION     },
    {   "unl_reset",            byRef (&doUnlReset),            Role::ADMIN,   NO_CONDITION     },
    {   "unl_score",            byRef (&doUnlScore),            Role::ADMIN,   NO_CONDITION     },
    {   "validation_create",    byRef (&doValidationCreate),    Role::ADMIN,   NO_CONDITION     },
    {   "validation_seed",      byRef (&doValidationSeed),      Role::ADMIN,   NO_CONDITION     },
    {   "wallet_propose",       byRef (&doWalletPropose),       Role::ADMIN,   NO_CONDITION     },
    {   "wallet_seed",          byRef (&doWalletSeed),          Role::ADMIN,   NO_CONDITION     },
	 
    // Evented methods
    {   "subscribe",            byRef (&doSubscribe),           Role::USER,  NO_CONDITION     },
    {   "unsubscribe",          byRef (&doUnsubscribe),         Role::USER,  NO_CONDITION     },
});

} // namespace

const Handler* getHandler(std::string const& name) {
    return HANDLERS.getHandler(name);
}

} // RPC
} // truechain
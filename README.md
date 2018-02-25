# truechain-testnet-core

![](images/truechain.png)
##TrueChain 初链: The Next Generation Public Blockchain for Real Commercial Applications

This repo is TrueChain PBFT testnet.

TrueChain is a commercial blockchain application platform that built with 
improved PBFT consensus. It is decentralized, secure, low-cost, and extremely fast.
It provides nearly real-time solutions to a variety of high-performance applications,
which is not met by current blockchain solutions.

Applications are built with smart contracts. TrueChain testnet supports Turing-Complete 
smart contract scripting in Lua, and very efficient VM. People or organizations who want 
to publish their own applications on TrueChain will find it much easier, faster, and cheaper
than solutions in the market.

TrueChain starts with digital advertising industry, where trust is missing. A lot of
scenarios in this industry could be implemented in the form of smart contracts. However it
is not limited to the industry, various commercial dapps from multiple industries will
emerge on TrueChain.

TRUE is the token on the blockchain. However, we support all kinds of custom tokens.
On TrueChain, people can make transactions globally with very low transaction fees. 

The test nets are for Dapp testing before TrueChain consensus is released and combined with
infrastructures for Dapps & management. There will be two test nets: one based on PBFT (this one),
the other based on Fabric infrastructure, which will be deployed soon.

Our testnet development team is and will be continously supported by members from Skywell Labs, Hyperledger and DoraHacks community.

## Development

### Compile

see `doc/compile.md`
..or use docker compose as described below..

### Run

Step 1: Install `docker-compose`


Step 2: Copy `env.example` to `.env` in same folder. Then, build and run:

```
$  docker-compose up --build -d
```

Step 3: See if the test page is accessible at `<your docker host IP>:5020` (as the 5020 host port is mapped to container port).

Check peer logs for debugging. They should look like:

```
$ docker-compose logs peer 
```

..which should be something like:

```
Attaching to truechaintestnetcore_peer_1
peer_1     | ERROR 2003 (HY000): Can't connect to MySQL server on 'mysqldb' (111)
peer_1     | Can't connect to mysqldb, retrying after 5 seconds..
peer_1     | ERROR 2003 (HY000): Can't connect to MySQL server on 'mysqldb' (111)
peer_1     | Can't connect to mysqldb, retrying after 5 seconds..
peer_1     | ERROR 2003 (HY000): Can't connect to MySQL server on 'mysqldb' (111)
peer_1     | Can't connect to mysqldb, retrying after 5 seconds..
peer_1     | Launching child 1Loading: "./truechaind.cfg"
peer_1     | m_name: /data/db/rocksdb
peer_1     | get rocksdb status: [0]
peer_1     | 2018-Feb-20 13:10:24 JobQueue:NFO Auto-tuning to 6 validation/transaction/proposal threads
peer_1     | 2018-Feb-20 13:10:24 LedgerMaster:NFO Validation quorum: 2
peer_1     | 2018-Feb-20 13:10:24 Application:NFO Root master seed: snoPBjXtMeMyMHUVTgbuqAfg1SUTb
peer_1     | 2018-Feb-20 13:10:24 Application:NFO Root account: jHb9CJAWyB4jr91VRWn96DkukG4bwdtyTh
peer_1     | 2018-Feb-20 13:10:24 LedgerMaster:NFO PushLedger: F8D2EBC9406BFA71E984379DEC5DEFA3FA0539BA726B479284F0F439DA5104D1
peer_1     | 2018-Feb-20 13:10:24 OrderBookDB:DBG Advancing from 0 to 3
peer_1     | 2018-Feb-20 13:10:24 OrderBookDB:DBG OrderBookDB::update>
peer_1     | 2018-Feb-20 13:10:24 OrderBookDB:DBG OrderBookDB::update< 0 books found
peer_1     | NodeIdentity: Creating.
peer_1     | NodeIdentity: Created.
peer_1     | NodeIdentity: n9Mskb72jpDjEfZNw8p5S4CxcB7B48jtKFeKBaAFV6MwHKznBXec
peer_1     | 2018-Feb-20 13:10:24 UniqueNodeList:DBG Validator fetch updated: not-a-date-time
peer_1     | 2018-Feb-20 13:10:24 UniqueNodeList:DBG Validator score updated: not-a-date-time
peer_1     | 2018-Feb-20 13:10:24 UniqueNodeList:NFO Bootstrapping UNL: loading from 'validators.txt'.
peer_1     | 2018-Feb-20 13:10:24 UniqueNodeList:WRN validators.txt not found: "validators.txt"
peer_1     | 2018-Feb-20 13:10:24 UniqueNodeList:NFO Bootstrapping UNL: loading from 2 '"./truechaind.cfg"'. 
peer_1     | 2018-Feb-20 13:10:24 UniqueNodeList:NFO Node Public: n94Jrp5oiYm2oeQGdNDG9WGW8Za7EqVrS14AoW7d4EEafKXXaj8d v01
peer_1     | 2018-Feb-20 13:10:24 UniqueNodeList:NFO Node Public: n9Me3g8iGNud1NifdLJDJ9r43Viwv8R1wwfXuBc7ysqjXp5Ffkup v02
peer_1     | 2018-Feb-20 13:10:24 UniqueNodeList:NFO Node Public: n9MZyC6awRPxc6ToMPm9RXiVcME2sVdSM6Z1Jwy9fmm1DSKbSjTz v03
peer_1     | 2018-Feb-20 13:10:24 UniqueNodeList:NFO Node Public: n9MoU2GfsLgNU5PZH7a1m1Vgt7CdaJB7AAuUSShpKLQoXgvEDrjE v04
peer_1     | 2018-Feb-20 13:10:24 UniqueNodeList:NFO Node Public: n9LSTMhNGGvXjezM5xCDPBkemUWU57bZTvqViCrarF1gPS4kauWz v05
peer_1     | 2018-Feb-20 13:10:24 UniqueNodeList:NFO Node Public: n9KkXzGUtVud3ACD69Z1D8ULtM7KUo8u2X3EzPhjq3HLkgkhBexa v06
peer_1     | 2018-Feb-20 13:10:24 TaggedCache:DBG Validations target size set to 256
peer_1     | 2018-Feb-20 13:10:24 TaggedCache:DBG Validations target age set to 500000000000 nanoseconds
peer_1     | 2018-Feb-20 13:10:24 TaggedCache:DBG NodeStore target size set to 32768
peer_1     | 2018-Feb-20 13:10:24 TaggedCache:DBG NodeStore target age set to 90000000000 nanoseconds
peer_1     | 2018-Feb-20 13:10:24 TaggedCache:DBG LedgerCache target size set to 128
peer_1     | 2018-Feb-20 13:10:24 TaggedCache:DBG LedgerCache target age set to 90000000000 nanoseconds
peer_1     | 2018-Feb-20 13:10:24 TaggedCache:DBG LedgerEntryCache target size set to 8192
peer_1     | 2018-Feb-20 13:10:24 TaggedCache:DBG LedgerEntryCache target age set to 60000000000 nanoseconds
peer_1     | 2018-Feb-20 13:10:24 TaggedCache:DBG TreeNodeCache target size set to 256000
peer_1     | 2018-Feb-20 13:10:24 TaggedCache:DBG TreeNodeCache target age set to 60000000000 nanoseconds
peer_1     | 2018-Feb-20 13:10:24 Server:NFO Opened 'port_rpc_admin_local' (ip=0.0.0.0:5050, admin IPs:0.0.0.0, http)
peer_1     | 2018-Feb-20 13:10:24 Server:NFO Opened 'port_peer' (ip=0.0.0.0:50338, peer)
peer_1     | Startup RPC: 2018-Feb-20 13:10:24 WebSocket:WRN Websocket: creating endpoint 'port_ws_public' (ip=0.0.0.0:5020, ws)
peer_1     | 
peer_1     | {
peer_1     | 	"command" : "log_level",
peer_1     | 	"severity" : "warning"
peer_1     | }
peer_1     | 
peer_1     | Result: {}
peer_1     | 
peer_1     | 2018-Feb-20 13:10:24 WebSocket:WRN Websocket: listening on 'port_ws_public' (ip=0.0.0.0:5020, ws)
peer_1     | 2018-Feb-20 13:10:35 LedgerConsensus:WRN Sending partial validation

```

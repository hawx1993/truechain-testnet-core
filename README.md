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
scenarios in this industry could be implemented in the form of smart contracts.

TRUE is the token on the blockchain. However, we support all kinds of custom tokens.
On TrueChain, people can make transactions globally with very low transaction fees. 

Validating nodes on True Chain performs key roles. Such nodes can be any kind of server,
e.g. AWS, DO, ALICLOUD, or servers physically located and configured locally in a company
or an organization. Nodes spread around the world and communicate under TrueChain's
network protocol. Transactions are verified using TrueChain's protocol, an improved practical BFT protocol.

Validating nodes play as full nodes. Storage is local to the node but distributed across 
all nodes.

TrueChain is solving some important problems all BFT and other blockchain protocols
face, to scale the network in order to meet high-performance requirements.

1. TrueChain is enabling a real public PBFT blockchain. Unlimited nodes can join the network to achieve full decentralization.
2. TrueChain is applying a dynamic configuration protocol to the network so that nodes join
freely and quit freely, with guarantee on node-connectivity (so that the consensus does
not break).
3. A protocol for Collaborative so that validating nodes have incentives to join.
Note that PBFT blockchains normally have no fees for validating nodes -- a great limit
to scale and be truely public. While in POW systems nodes compete to mine, PBFT nodes have
to collaborate and share. This is achieved by a public-visible, initial smart contract.
4. A delegation protocol to solve the PBFT throughput problem.

Our nestnet development team is and will be continously supported by members from Skywell Labs, Hyperledger and DoraHacks community.

## Development

### Compile

see `doc/compile.md`

### Run

See all options:

```
$ ./bin/truechainConsole
Usage: ./bin/truechainConsole {start|stop|restart|status|fetch|uptime|command|test|chk}
```

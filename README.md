# Extra Tool
A tiny, rudimentary tool for analyzing transaction extranonces in Monero and CryptoNote transactions.  Currently, only input as a hex string is supported, as well as interpretations of the extra fields being limited to `tx_pubkeys` and `additional_tx_pubkeys`.  Support for other extra field types will be added later. 

This tool is distributed under the WTFPL.

See [LICENSE](LICENSE.md).

**Compile with:** `g++ extra_tool.cpp -o extra_tool`

Then follow the prompts.  Only a 1-byte padding is currently supported.


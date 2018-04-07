//
//  block_py.hpp
//  blocksci
//
//  Created by Harry Kalodner on 3/14/18.
//

#ifndef block_py_h
#define block_py_h

#include <blocksci/chain/block.hpp>
#include <blocksci/chain/algorithms.hpp>

#include <pybind11/pybind11.h>

#include <range/v3/view/any_view.hpp>

void init_block(pybind11::module &m);

template <typename Class, typename FuncApplication, typename FuncDoc>
void addBlockMethods(Class &cl, FuncApplication func, FuncDoc func2) {
    namespace py = pybind11;
    using namespace blocksci;
    cl
    .def_property_readonly("hash", func([](const Block &block) {
        return block.getHash();
    }), func2("Hash of this block"))
    .def_property_readonly("version", func([](const Block &block) {
        return block.version();
    }), func2("Protocol version specified in block header"))
    .def_property_readonly("timestamp", func([](const Block &block) {
        return block.timestamp();
    }), func2("Creation timestamp specified in block header"))
    .def_property_readonly("time", func([](const Block &block) {
        return block.getTime();
    }), func2("Datetime object created from creation timestamp"))
    .def_property_readonly("bits", func([](const Block &block) {
        return block.bits();
    }), func2("Difficulty threshold specified in block header"))
    .def_property_readonly("nonce", func([](const Block &block) {
        return block.nonce();
    }), func2("Nonce specified in block header"))
    .def_property_readonly("height", func([](const Block &block) {
        return block.height();
    }), func2("Height of the block in the blockchain"))
    .def_property_readonly("coinbase_param", func([](const Block &block) {
        return py::bytes(block.coinbaseParam());
    }), func2("Data contained within the coinbase transaction of this block"))
    .def_property_readonly("coinbase_tx", func([](const Block &block) {
        return block.coinbaseTx();
    }), func2("Return the coinbase transaction in this block"))
    .def_property_readonly("size_bytes", func([](const Block &block) {
        return block.totalSize();
    }), func2("Returns the total size of the block in bytes"))
    .def_property_readonly("fee", func([](const Block &block) {
        return totalFee(block);
    }), func2("The sum of the transaction fees contained in this block"))
    .def_property_readonly("revenue", func([](const Block &block) {
        return totalOutputValue(block[0]);
    }), func2("Total reward received by the miner of this block"))
    .def_property_readonly("base_size", func([](const Block &block) {
        return block.baseSize();
    }), func2("The size of the non-segwit data in bytes"))
    .def_property_readonly("total_size", func([](const Block &block) {
        return block.totalSize();
    }), func2("The size all block data in bytes"))
    .def_property_readonly("virtual_size", func([](const Block &block) {
        return block.virtualSize();
    }), func2("The weight of the block divided by 4"))
    .def_property_readonly("weight", func([](const Block &block) {
        return block.weight();
    }), func2("Three times the base size plus the total size"))
    .def_property_readonly("input_value", func([](const Block &block) {
        return totalInputValue(block);
    }), func2("Returns the sum of the value of all of the inputs included in this block"))
    .def_property_readonly("output_value", func([](const Block &block) {
        return totalOutputValue(block);
    }), func2("Returns the sum of the value of all of the outputs included in this block"))
    .def_property_readonly("input_count", func([](const Block &block) {
        return inputCount(block);
    }), func2("Returns total number of inputs included in this block"))
    .def_property_readonly("output_count", func([](const Block &block) {
        return outputCount(block);
    }), func2("Returns total number of outputs included in this block"))
    ;
}

template <typename Class, typename FuncApplication>
void addBlockRangeMethods(Class &cl, FuncApplication func) {
    using namespace blocksci;
    using Range = typename Class::type;
    cl
    .def_property_readonly("txes", [=](Range &range) -> ranges::any_view<Transaction>  {
        return func(range, [=](auto && r) -> ranges::any_view<Transaction> {
            return txes(r);
        });
    }, "A list of the inputs of the listed blocks")
    .def_property_readonly("inputs", [=](Range &range) -> ranges::any_view<Input>  {
        return func(range, [=](auto && r) -> ranges::any_view<Input> {
            return inputs(r);
        });
    }, "A list of the inputs of the listed blocks")
    .def_property_readonly("outputs", [=](Range &range) -> ranges::any_view<Output>  {
        return func(range, [=](auto && r) -> ranges::any_view<Output> {
            return outputs(r);
        });
    }, "A list of the outputs of the listed blocks")
    ;
}

#endif /* block_py_h */

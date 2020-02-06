/* Copyright 2020 The TensorFlow Quantum Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#include "tensorflow_quantum/core/src/circuit.h"

#include <cstdlib>

#include "gtest/gtest.h"

namespace tfq {
namespace {

float RandomFloat() {
  return static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
}

void GetTestGate1q(Gate* test_gate) {
  std::array<float, 8> matrix;
  std::generate(matrix.begin(), matrix.begin() + 8, RandomFloat);
  *test_gate = Gate(18, 3, matrix);
}

void GetTestGate2q(Gate* test_gate) {
  std::array<float, 32> matrix;
  std::generate(matrix.begin(), matrix.begin() + 32, RandomFloat);
  *test_gate = Gate(19, 3, 4, matrix);
}

TEST(CircuitTest, Gate0q) {
  Gate test_gate, true_gate;

  // check individual element equality manually
  ASSERT_EQ(test_gate.time, true_gate.time);
  ASSERT_EQ(test_gate.num_qubits, true_gate.num_qubits);

  // check equality operator overload
  test_gate.time = true_gate.time + 1;
  ASSERT_NE(test_gate, true_gate);
  test_gate.time = true_gate.time;

  test_gate.num_qubits = true_gate.num_qubits + 1;
  ASSERT_NE(test_gate, true_gate);
  test_gate.num_qubits = true_gate.num_qubits;

  ASSERT_EQ(test_gate, true_gate);
}

TEST(CircuitTest, Gate1q) {
  Gate test_gate;
  GetTestGate1q(&test_gate);
  Gate true_gate;
  true_gate = test_gate;

  // check individual element equality manually
  ASSERT_EQ(test_gate.time, true_gate.time);
  ASSERT_EQ(test_gate.num_qubits, true_gate.num_qubits);
  ASSERT_EQ(test_gate.qubits[0], true_gate.qubits[0]);
  for (int i = 0; i < 8; i++) {
    ASSERT_EQ(test_gate.matrix[i], true_gate.matrix[i]);
  }

  // check equality operator overload
  test_gate.time = true_gate.time + 1;
  ASSERT_NE(test_gate, true_gate);
  test_gate.time = true_gate.time;

  test_gate.num_qubits = true_gate.num_qubits + 1;
  ASSERT_NE(test_gate, true_gate);
  test_gate.num_qubits = true_gate.num_qubits;

  test_gate.qubits[0] = true_gate.qubits[0] + 1;
  ASSERT_NE(test_gate, true_gate);
  test_gate.qubits[0] = true_gate.qubits[0];

  test_gate.matrix[7] = true_gate.matrix[7] + 1;
  ASSERT_NE(test_gate, true_gate);
  test_gate.matrix[7] = true_gate.matrix[7];

  ASSERT_EQ(test_gate, true_gate);
}

TEST(CircuitTest, Gate2q) {
  Gate test_gate;
  GetTestGate2q(&test_gate);
  Gate true_gate;
  true_gate = test_gate;

  // check individual element equality manually
  ASSERT_EQ(test_gate.time, true_gate.time);
  ASSERT_EQ(test_gate.num_qubits, true_gate.num_qubits);
  ASSERT_EQ(test_gate.qubits[0], true_gate.qubits[0]);
  ASSERT_EQ(test_gate.qubits[1], true_gate.qubits[1]);
  for (int i = 0; i < 32; i++) {
    ASSERT_EQ(test_gate.matrix[i], true_gate.matrix[i]);
  }

  // check equality operator overload
  test_gate.time = true_gate.time + 1;
  ASSERT_NE(test_gate, true_gate);
  test_gate.time = true_gate.time;

  test_gate.num_qubits = true_gate.num_qubits + 1;
  ASSERT_NE(test_gate, true_gate);
  test_gate.num_qubits = true_gate.num_qubits;

  test_gate.qubits[0] = true_gate.qubits[0] + 1;
  ASSERT_NE(test_gate, true_gate);
  test_gate.qubits[0] = true_gate.qubits[0];

  test_gate.qubits[1] = true_gate.qubits[1] + 1;
  ASSERT_NE(test_gate, true_gate);
  test_gate.qubits[1] = true_gate.qubits[1];

  test_gate.matrix[31] = true_gate.matrix[31] + 1;
  ASSERT_NE(test_gate, true_gate);
  test_gate.matrix[31] = true_gate.matrix[31];

  ASSERT_EQ(test_gate, true_gate);
}

TEST(CircuitTest, CircuitEmpty) {
  Circuit true_circuit, test_circuit;
  test_circuit.num_qubits = true_circuit.num_qubits = 53;

  // check equality operator overload
  test_circuit.num_qubits = true_circuit.num_qubits + 1;
  ASSERT_NE(test_circuit, true_circuit);
  test_circuit.num_qubits = true_circuit.num_qubits;
  ASSERT_EQ(test_circuit, true_circuit);
}

TEST(CircuitTest, CircuitFull) {
  Circuit true_circuit, test_circuit;
  test_circuit.num_qubits = true_circuit.num_qubits = 53;

  Gate gate_0, gate_1, gate_2;
  GetTestGate1q(&gate_1);
  GetTestGate2q(&gate_2);
  test_circuit.gates.push_back(gate_0);
  test_circuit.gates.push_back(gate_1);
  test_circuit.gates.push_back(gate_2);
  true_circuit.gates.push_back(gate_0);
  true_circuit.gates.push_back(gate_1);
  true_circuit.gates.push_back(gate_2);

  // check equality operator overload
  test_circuit.num_qubits = true_circuit.num_qubits + 1;
  ASSERT_NE(test_circuit, true_circuit);
  test_circuit.num_qubits = true_circuit.num_qubits;
  test_circuit.gates[2] = true_circuit.gates[0];
  ASSERT_NE(test_circuit, true_circuit);
  test_circuit.gates[2] = true_circuit.gates[2];
  ASSERT_EQ(test_circuit, true_circuit);
}

}  // namespace
}  // namespace tfq

using System;
using System.Text;
using System.Collections.Generic;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System.Runtime.InteropServices;
using System.IO;

namespace MiniCMSTestFixture
{
    /// <summary>
    /// Summary description for AssemblerUnitTest
    /// </summary>
    [TestClass()]
    public class AssemblerUnitTest
    {
        [DllImport("bitepicness.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        internal static extern int Test_GetOpCode(String op, StringBuilder opCode, StringBuilder funcCode);

        [DllImport("bitepicness.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void Test_TranslateRegister(String register, StringBuilder registerCode);

        [DllImport("bitepicness.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void Test_ConvertDecToBinary(int dec, int bitnum, [In, Out] ref int numErrors, StringBuilder bin);

        public enum OpTypes
        {
            R = 0,
            I = 1,
            J = 2,
            M = 3,
            L = 4,
            SYSI = 5,
            SYSN = 6,
            SYSR = 7,
            SYSRR = 8
        };

        public AssemblerUnitTest()
        {
        }

        private TestContext testContextInstance;

        /// <summary>
        ///Gets or sets the test context which provides
        ///information about and functionality for the current test run.
        ///</summary>
        public TestContext TestContext
        {
            get
            {
                return testContextInstance;
            }
            set
            {
                testContextInstance = value;
            }
        }

        #region Additional test attributes
        //
        // You can use the following additional attributes as you write your tests:
        //
        // Use ClassInitialize to run code before running the first test in the class
        // [ClassInitialize()]
        // public static void MyClassInitialize(TestContext testContext) { }
        //
        // Use ClassCleanup to run code after all tests in a class have run
        // [ClassCleanup()]
        // public static void MyClassCleanup() { }
        //
        // Use TestInitialize to run code before running each test 
        //[TestInitialize()]
        //public void MyTestInitialize()
        //{
        //}
        //
        // Use TestCleanup to run code after each test has run
        // [TestCleanup()]
        // public void MyTestCleanup() { }
        //
        #endregion

        [TestCategory("Unit Tests"), TestMethod()]
        public void TestOperations()
        {
            TestOperation("j", "00000", OpTypes.J);
            TestOperation("jal", "00001", OpTypes.J);
            TestOperation("beq", "1010", OpTypes.R);
            TestOperation("bne", "1011", OpTypes.R);
            TestOperation("bgt", "1000", OpTypes.R);
            TestOperation("blt", "1001", OpTypes.R);
            TestOperation("lwn", "1110", OpTypes.R);
            TestOperation("swn", "1111", OpTypes.R);
            TestOperation("ldw", "1100", OpTypes.R);
            TestOperation("sdw", "1101", OpTypes.R);
            TestOperationWithFuncCode("rp", "01000", "011", OpTypes.SYSI);
            TestOperationWithFuncCode("wp", "01000", "010", OpTypes.SYSI);
            TestOperationWithFuncCode("mfc0", "01000", "001", OpTypes.SYSRR);
            TestOperationWithFuncCode("mtc0", "01000", "000", OpTypes.SYSRR);
            TestOperation("addi", "01100", OpTypes.I);
            TestOperation("ldi", "00101", OpTypes.L);
            TestOperation("ldl", "01001", OpTypes.L);
            TestOperation("ori", "01101", OpTypes.I);
            TestOperation("slli", "01111", OpTypes.I);
            TestOperationWithFuncCode("add", "01110", "000", OpTypes.M);
            TestOperationWithFuncCode("and", "01110", "001", OpTypes.M);
            TestOperationWithFuncCode("sll", "01110", "011", OpTypes.M);
            TestOperationWithFuncCode("sub", "01110", "110", OpTypes.M);
            TestOperation("jr", "00010", OpTypes.M);
            TestOperation("move", "00100", OpTypes.M);
            TestOperation("neg", "00110", OpTypes.M);
            TestOperation("nop", "00100", OpTypes.M);
            TestOperation("not", "00111", OpTypes.M);
            TestOperationWithFuncCode("or", "01110", "010", OpTypes.M);
            TestOperationWithFuncCode("jalr", "00011", "000", OpTypes.SYSR);
            TestOperationWithFuncCode("eni", "01000", "101", OpTypes.SYSN);
            TestOperationWithFuncCode("disi", "01000", "100", OpTypes.SYSN);
            TestOperationWithFuncCode("swi", "01000", "110", OpTypes.SYSR);
        }

        internal void TestOperation(String op, String expectedOpCode, OpTypes expectedType)
        {
            int bufferLength = 10;
            StringBuilder opCodeResult = new StringBuilder(bufferLength);
            StringBuilder funcCodeResult = new StringBuilder(bufferLength);
            int opTypeResult = 0;
            opTypeResult = Test_GetOpCode(op, opCodeResult, funcCodeResult);
            Assert.AreEqual(expectedOpCode, opCodeResult.ToString());
            Assert.AreEqual((int)expectedType, opTypeResult);
        }

        internal void TestOperationWithFuncCode(String op, String expectedOpCode, String expectedFuncCode, OpTypes expectedType)
        {
            int bufferLength = 10;
            StringBuilder opCodeResult = new StringBuilder(bufferLength);
            StringBuilder funcCodeResult = new StringBuilder(bufferLength);
            int opTypeResult = 0;
            opTypeResult = Test_GetOpCode(op, opCodeResult, funcCodeResult);
            Assert.AreEqual(expectedOpCode, opCodeResult.ToString());
            Assert.AreEqual(expectedFuncCode, funcCodeResult.ToString());
            Assert.AreEqual((int)expectedType, opTypeResult);
        }
        [TestCategory("Unit Tests"), TestMethod()]
        public void TestRegisters()
        {
            this.TestContext.WriteLine("Starting TestRegisters...");
            TestRegister("$zero", "0000", true);
            TestRegister("$0", "0000", true);
            TestRegister("$at", "0001", true);
            TestRegister("$1", "0001", true);
            TestRegister("$v", "0010", true);
            TestRegister("$2", "0010", true);
            TestRegister("$a", "0011", true);
            TestRegister("$3", "0011", true);
            TestRegister("$s0", "0100", true);
            TestRegister("$4", "0100", true);
            TestRegister("$s1", "0101", true);
            TestRegister("$5", "0101", true);
            TestRegister("$os0", "0110", true);
            TestRegister("$6", "0110", true);
            TestRegister("$os1", "0111", true);
            TestRegister("$7", "0111", true);
            TestRegister("$k0", "1000", true);
            TestRegister("$8", "1000", true);
            TestRegister("$k1", "1001", true);
            TestRegister("$9", "1001", true);
            TestRegister("$k2", "1010", true);
            TestRegister("$10", "1010", true);
            TestRegister("$fp", "1011", true);
            TestRegister("$11", "1011", true);
            TestRegister("$gp", "1100", true);
            TestRegister("$12", "1100", true);
            TestRegister("$sp", "1101", true);
            TestRegister("$13", "1101", true);
            TestRegister("$rr", "1110", true);
            TestRegister("$14", "1110", true);
            TestRegister("$ra", "1111", true);
            TestRegister("$15", "1111", true);
            TestRegister("$epc", "0000", true);
            TestRegister("$cause", "0001", true);
            TestRegister("$br", "0010", true);
            TestRegister("$im", "0011", true);
            TestRegister("$ostmp", "0100", true);
            TestRegister("$mode", "0101", true);
            this.TestContext.WriteLine("Done Running TestRegisters.");
        }

        internal void TestRegister(String reg, String expectedRegCode, bool expectedPass)
        {
            this.TestContext.WriteLine("Testing " + reg + ".");
            int bufferLength = 10;
            StringBuilder regCodeResult = new StringBuilder(bufferLength);
            int numErrors = 1;
            Test_TranslateRegister(reg, regCodeResult);
            if (expectedPass)
            {
                Assert.AreEqual(expectedRegCode, regCodeResult.ToString());
            }
            else
            {
                Assert.IsTrue(numErrors > 0);
            }
        }

        [TestCategory("Unit Tests"), TestMethod()]
        public void TestDecToBinConversions()
        {
            //Test limits of input number, including exceeding.
            TestDecToBinConversion(5, 16, "0000000000000101", true);
            TestDecToBinConversion(-5, 16, "1111111111111011", true);
            TestDecToBinConversion(128, 16, "0000000010000000", true);
            TestDecToBinConversion(-128, 16, "1111111110000000", true);
            TestDecToBinConversion(2688, 16, "0000101010000000", true);
            TestDecToBinConversion(-2688, 16, "1111010110000000", true);
            TestDecToBinConversion(32767, 16, "0111111111111111", true);
            TestDecToBinConversion(-32767, 16, "1000000000000001", true);
            TestDecToBinConversion(-32768, 16, "1000000000000000", true);
            TestDecToBinConversion(0, 16, "0000000000000000", true);
            TestDecToBinConversion(5, 32, "00000000000000000000000000000101", true);
            TestDecToBinConversion(-5, 32, "11111111111111111111111111111011", true);
            TestDecToBinConversion(128, 32, "00000000000000000000000010000000", true);
            TestDecToBinConversion(-128, 32, "11111111111111111111111110000000", true);
            TestDecToBinConversion(2688, 32, "00000000000000000000101010000000", true);
            TestDecToBinConversion(-2688, 32, "11111111111111111111010110000000", true);
            TestDecToBinConversion(32767, 32, "00000000000000000111111111111111", true);
            TestDecToBinConversion(-32767, 32, "11111111111111111000000000000001", true);
            TestDecToBinConversion(-32768, 32, "11111111111111111000000000000000", true);
            TestDecToBinConversion(0, 32, "00000000000000000000000000000000", true);
            TestDecToBinConversion(32768, 16, "", false);
            TestDecToBinConversion(-32769, 16, "", false);
        }

        internal void TestDecToBinConversion(int dec, int bitnum, String expectedBin, bool expectedPass)
        {
            int bufferLength = bitnum + 1;
            StringBuilder actualBin = new StringBuilder(bufferLength);
            int numErrors = 0;
            Test_ConvertDecToBinary(dec, bitnum, ref numErrors, actualBin);
            if (expectedPass)
            {
                Assert.AreEqual(expectedBin, actualBin.ToString());
            }
            else
            {
                Assert.IsTrue(numErrors > 0);
            }
        }
    }

    
    /// <summary>
    /// Summary description for AssemblerIntegrationTest
    /// </summary>
    [TestClass()]
    public class AssemblerIntegrationTest
    {
        [DllImport("bitepicness.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void Test_TranslateSingleInstruction(String assemblyLine, int strLen, int numInstructions, StringBuilder binaryAsm);

        [DllImport("bitepicness.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void Test_TranslateInstruction(String fileName, int fileLength, StringBuilder translatedAsm);

        public AssemblerIntegrationTest()
        {
        }

        private TestContext testContextInstance;

        /// <summary>
        ///Gets or sets the test context which provides
        ///information about and functionality for the current test run.
        ///</summary>
        public TestContext TestContext
        {
            get
            {
                return testContextInstance;
            }
            set
            {
                testContextInstance = value;
            }
        }

        #region Additional test attributes
        //
        // You can use the following additional attributes as you write your tests:
        //
        // Use ClassInitialize to run code before running the first test in the class
        // [ClassInitialize()]
        // public static void MyClassInitialize(TestContext testContext) { }
        //
        // Use ClassCleanup to run code after all tests in a class have run
        // [ClassCleanup()]
        // public static void MyClassCleanup() { }
        //
        // Use TestInitialize to run code before running each test 
        //[TestInitialize()]
        //public void MyTestInitialize()
        //{
        //}
        //
        // Use TestCleanup to run code after each test has run
        // [TestCleanup()]
        // public void MyTestCleanup() { }
        //
        #endregion
        
        [TestCategory("Unit Tests"), TestMethod()]
        public void AddImmediateTest()
        {
            TestSingleInstruction("addi $gp, -1", "memory_initialization_radix=2;\nmemory_initialization_vector=\n0110011001111111;");
        }

        [TestCategory("Unit Tests"), TestMethod()]
        public void ShiftLeftTest()
        {
            TestSingleInstruction("sll $gp, $0", "memory_initialization_radix=2;\nmemory_initialization_vector=\n0111011000000011;");
        }

        [TestCategory("Unit Tests"), TestMethod()]
        public void ShiftLeftImmediateTest()
        {
            TestSingleInstruction("slli $gp, 5", "memory_initialization_radix=2;\nmemory_initialization_vector=\n0111111000000101;");
        }

        [TestCategory("Unit Tests"), TestMethod()]
        public void SubTest()
        {
            TestSingleInstruction("sub $gp, $0", "memory_initialization_radix=2;\nmemory_initialization_vector=\n0111011000000110;");
        }

        [TestCategory("Unit Tests"), TestMethod()]
        public void SWITest()
        {
            TestSingleInstruction("swi $gp", "memory_initialization_radix=2;\nmemory_initialization_vector=\n0100011000000110;");
        }

        [TestCategory("Unit Tests"), TestMethod()]
        public void MFC0BRTest()
        {
            TestSingleInstruction("mfc0 $at, $br", "memory_initialization_radix=2;\nmemory_initialization_vector=\n0100000010010001;");
        }

        [TestCategory("Unit Tests"), TestMethod()]
        public void AddShiftTest()
        {
            TestMultipleInstructions("addi $gp, -1\nsll $gp, $0", 2, "memory_initialization_radix=2;\nmemory_initialization_vector=\n0110011001111111,\n0111011000000011;");
        }

        [TestCategory("Unit Tests"), TestMethod()]
        public void LATest()
        {
            TestMultipleInstructions("L1: add $s0, $s1\nla $s0, L1", 2, "memory_initialization_radix=2;\nmemory_initialization_vector=\n0111001000101000,\n0100100010000000,\n0000000000000000,\n0100101000000000,\n0000000000000000,\n0111100010010000,\n0111011100100000,\n0010001001110000;");
        }

        [TestCategory("Unit Tests"), TestMethod()]
        public void PostLATest()
        {
            TestMultipleInstructions("la $s0, L1\nL1: add $s0, $s1", 2, "memory_initialization_radix=2;\nmemory_initialization_vector=\n0100100010000000,\n0000000000000000,\n0100101000000000,\n0000000000000111,\n0111100010010000,\n0111011100100000,\n0010001001110000,\n0111001000101000;");
        }

        internal void TestSingleInstruction(String originalStr, String theoreticalString)
        {
            int bufferLength = 1000;
            StringBuilder translatedAssembly = new StringBuilder(bufferLength);
            Test_TranslateSingleInstruction(originalStr + "\n", bufferLength, 1, translatedAssembly);
            Assert.AreEqual(theoreticalString, translatedAssembly.ToString());
        }

        internal void TestMultipleInstructions(String originalStr, int numInstructions, String theoreticalString)
        {
            int bufferLength = 1000;
            StringBuilder translatedAssembly = new StringBuilder(bufferLength);
            Test_TranslateSingleInstruction(originalStr, bufferLength, numInstructions, translatedAssembly);
            Assert.AreEqual(theoreticalString, translatedAssembly.ToString());
        }

        [TestCategory("Integration Tests"), TestMethod()]
        public void AbsTest()
        {
            TestInstructionTranslation("AbsTest.asm", "AbsTest.testasm", true);
        }

        [TestCategory("Integration Tests"), TestMethod()]
        public void SimpleTest()
        {
            TestInstructionTranslation("SimpleTest.asm", "SimpleTest.testasm", true);
        }

        [TestCategory("Integration Tests"), TestMethod()]
        public void EuclidsTest()
        {
            TestInstructionTranslation("Euclids.asm", "Euclids.testasm", true);
        }

        internal void TestInstructionTranslation(String fileName, String testFileName, bool expectedPass)
        {
            FileInfo fi = new FileInfo(fileName);
            if (fi.Exists)
            {
                StringBuilder translatedAssembly = new StringBuilder((int)fi.Length);
                int numErrors = 1;
                Test_TranslateInstruction(fileName, (int)fi.Length, translatedAssembly);
                if (expectedPass)
                {
                    TextReader tr = new StreamReader(testFileName);
                    String testFileOut = tr.ReadToEnd();
                    tr.Close();
                    //Needed since output will only have new lines, and not carriage returns.
                    translatedAssembly.Replace("\n", "\r\n");
                    if (!testFileOut.Equals(translatedAssembly.ToString()))
                    {
                        TextWriter tw = new StreamWriter(fileName.Replace(".asm", ".failedasm"));
                        tw.Write(translatedAssembly);
                        tw.Close();
                    }
                    Assert.AreEqual(testFileOut, translatedAssembly.ToString());
                }
                else
                {
                    Assert.IsTrue(numErrors > 0);
                }
            }
            else
            {
                Assert.IsTrue(false);
            }
        }
    }
}

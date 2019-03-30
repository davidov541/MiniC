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
    /// Summary description for CompilerUnitTest
    /// </summary>
    [TestClass]
    public class CompilerArrayUnitTest
    {
        [DllImport("minic.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl, SetLastError = false)]
        [return: MarshalAs(UnmanagedType.I1)]
        internal static extern Boolean Test_ArrayOfInts_TypeCheck(StringBuilder errorOutput);

        [DllImport("minic.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl, SetLastError = false)]
        [return: MarshalAs(UnmanagedType.I1)]
        internal static extern Boolean Test_ArrayOfPointers_TypeCheck(StringBuilder errorOutput);

        [DllImport("minic.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl, SetLastError = false)]
        [return: MarshalAs(UnmanagedType.I1)]
        internal static extern Boolean Test_ArrayOfChars_TypeCheck(StringBuilder errorOutput);

        [DllImport("minic.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl, SetLastError = false)]
        [return: MarshalAs(UnmanagedType.I1)]
        internal static extern Boolean Test_ArrayWithStrangeIndicies_TypeCheck(StringBuilder errorOutput);

        [DllImport("minic.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl, SetLastError = false)]
        [return: MarshalAs(UnmanagedType.I1)]
        internal static extern Boolean Test_ArrayOfInts_FGGen(StringBuilder errorOutput);

        [DllImport("minic.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl, SetLastError = false)]
        [return: MarshalAs(UnmanagedType.I1)]
        internal static extern Boolean Test_ArrayOfPointers_FGGen(StringBuilder errorOutput);

        [DllImport("minic.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl, SetLastError = false)]
        [return: MarshalAs(UnmanagedType.I1)]
        internal static extern Boolean Test_ArrayOfChars_FGGen(StringBuilder errorOutput);

        [DllImport("minic.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl, SetLastError = false)]
        [return: MarshalAs(UnmanagedType.I1)]
        internal static extern Boolean Test_ArrayWithStrangeIndicies_FGGen(StringBuilder errorOutput);

        public CompilerArrayUnitTest()
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
        // [TestInitialize()]
        // public void MyTestInitialize() { }
        //
        // Use TestCleanup to run code after each test has run
        // [TestCleanup()]
        // public void MyTestCleanup() { }
        //
        #endregion

        [TestCategory("Unit Tests"), TestMethod]
        public void TestArrayOfInts_TypeCheck()
        {
            int bufferLen = 1000;
            StringBuilder errMsg = new StringBuilder(bufferLen);
            try
            {
                Boolean result = Test_ArrayOfInts_TypeCheck(errMsg);
                Assert.IsTrue(result);
            }
            catch (AssertFailedException e)
            {
                AssertFailedException exp = new AssertFailedException(errMsg.ToString(), e);
                throw exp;
            }
        }

        [TestCategory("Unit Tests"), TestMethod]
        public void TestArrayOfPointers_TypeCheck()
        {
            int bufferLen = 1000;
            StringBuilder errMsg = new StringBuilder(bufferLen);
            try
            {
                Boolean result = Test_ArrayOfPointers_TypeCheck(errMsg);
                Assert.IsTrue(result);
            }
            catch (AssertFailedException e)
            {
                AssertFailedException exp = new AssertFailedException(errMsg.ToString(), e);
                throw exp;
            }
        }

        [TestCategory("Unit Tests"), TestMethod]
        public void TestArrayOfChars_TypeCheck()
        {
            int bufferLen = 1000;
            StringBuilder errMsg = new StringBuilder(bufferLen);
            try
            {
                Boolean result = Test_ArrayOfChars_TypeCheck(errMsg);
                Assert.IsTrue(result);
            }
            catch (AssertFailedException e)
            {
                AssertFailedException exp = new AssertFailedException(errMsg.ToString(), e);
                throw exp;
            }
        }

        [TestCategory("Unit Tests"), TestMethod]
        public void TestArrayWithStrangeIndicies_TypeCheck()
        {
            int bufferLen = 1000;
            StringBuilder errMsg = new StringBuilder(bufferLen);
            try
            {
                Boolean result = Test_ArrayWithStrangeIndicies_TypeCheck(errMsg);
                Assert.IsTrue(result);
            }
            catch (AssertFailedException e)
            {
                AssertFailedException exp = new AssertFailedException(errMsg.ToString(), e);
                throw exp;
            }
        }

        [TestCategory("Unit Tests"), TestMethod]
        public void TestArrayOfInts_FGGen()
        {
            int bufferLen = 1000;
            StringBuilder errMsg = new StringBuilder(bufferLen);
            try
            {
                Boolean result = Test_ArrayOfInts_FGGen(errMsg);
                Assert.IsTrue(result);
            }
            catch (AssertFailedException e)
            {
                AssertFailedException exp = new AssertFailedException(errMsg.ToString(), e);
                throw exp;
            }
        }

        [TestCategory("Unit Tests"), TestMethod]
        public void TestArrayOfPointers_FGGen()
        {
            int bufferLen = 1000;
            StringBuilder errMsg = new StringBuilder(bufferLen);
            try
            {
                Boolean result = Test_ArrayOfPointers_FGGen(errMsg);
                Assert.IsTrue(result);
            }
            catch (AssertFailedException e)
            {
                AssertFailedException exp = new AssertFailedException(errMsg.ToString(), e);
                throw exp;
            }
        }

        [TestCategory("Unit Tests"), TestMethod]
        public void TestArrayOfChars_FGGen()
        {
            int bufferLen = 1000;
            StringBuilder errMsg = new StringBuilder(bufferLen);
            try
            {
                Boolean result = Test_ArrayOfChars_FGGen(errMsg);
                Assert.IsTrue(result);
            }
            catch (AssertFailedException e)
            {
                AssertFailedException exp = new AssertFailedException(errMsg.ToString(), e);
                throw exp;
            }
        }

        [TestCategory("Unit Tests"), TestMethod]
        public void TestArrayWithStrangeIndicies_FGGen()
        {
            int bufferLen = 1000;
            StringBuilder errMsg = new StringBuilder(bufferLen);
            try
            {
                Boolean result = Test_ArrayWithStrangeIndicies_FGGen(errMsg);
                Assert.IsTrue(result);
            }
            catch (AssertFailedException e)
            {
                AssertFailedException exp = new AssertFailedException(errMsg.ToString(), e);
                throw exp;
            }
        }
    }

    [TestClass]
    public class CompilerOptimizationUnitTest
    {
        [DllImport("minic.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl, SetLastError = false)]
        [return: MarshalAs(UnmanagedType.I1)]
        internal static extern Boolean Test_OptimizeUselessMoves(StringBuilder errMsg);

        [DllImport("minic.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl, SetLastError = false)]
        [return: MarshalAs(UnmanagedType.I1)]
        internal static extern Boolean Test_OptimizeBranches(StringBuilder errMsg);

        [DllImport("minic.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl, SetLastError = false)]
        [return: MarshalAs(UnmanagedType.I1)]
        internal static extern Boolean Test_OptimizeConstantAddExpressions(StringBuilder errorOutput);
        
        [DllImport("minic.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl, SetLastError = false)]
        [return: MarshalAs(UnmanagedType.I1)]
        internal static extern Boolean Test_OptimizeConstantBoolExpressions(StringBuilder errorOutput);

        [DllImport("minic.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl, SetLastError = false)]
        [return: MarshalAs(UnmanagedType.I1)]
        internal static extern Boolean Test_OptimizeConstantShiftExpressions(StringBuilder errorOutput);
        
        [DllImport("minic.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl, SetLastError = false)]
        [return: MarshalAs(UnmanagedType.I1)]
        internal static extern Boolean Test_OptimizeConstantUnaryExpressions(StringBuilder errorOutput);

        [DllImport("minic.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl, SetLastError = false)]
        [return: MarshalAs(UnmanagedType.I1)]
        internal static extern Boolean Test_OptimizeStackOperations(StringBuilder errorOutput);

        public CompilerOptimizationUnitTest()
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
        // [TestInitialize()]
        // public void MyTestInitialize() { }
        //
        // Use TestCleanup to run code after each test has run
        // [TestCleanup()]
        // public void MyTestCleanup() { }
        //
        #endregion

        [TestCategory("Unit Tests"), TestMethod]
        public void TestUselessMoveRemoval()
        {
            int bufferLen = 1000;
            StringBuilder errMsg = new StringBuilder(bufferLen);
            try
            {
                Boolean result = Test_OptimizeUselessMoves(errMsg);
                Assert.IsTrue(result);
            }
            catch (AssertFailedException e)
            {
                AssertFailedException exp = new AssertFailedException(errMsg.ToString(), e);
                throw exp;
            }
        }

        [TestCategory("Unit Tests"), TestMethod]
        public void TestOptimizeBranches()
        {
            int bufferLen = 1000;
            StringBuilder errMsg = new StringBuilder(bufferLen);
            try
            {
                Boolean result = Test_OptimizeBranches(errMsg);
                Assert.IsTrue(result);
            }
            catch (AssertFailedException e)
            {
                AssertFailedException exp = new AssertFailedException(errMsg.ToString(), e);
                throw exp;
            }
        }

        [TestCategory("Unit Tests"), TestMethod]
        public void TestConstantAddExpressions()
        {
            int bufferLen = 1000;
            StringBuilder errMsg = new StringBuilder(bufferLen);
            try
            {
                Boolean result = Test_OptimizeConstantAddExpressions(errMsg);
                Assert.IsTrue(result);
            }
            catch (AssertFailedException e)
            {
                AssertFailedException exp = new AssertFailedException(errMsg.ToString(), e);
                throw exp;
            }
        }

        [TestCategory("Unit Tests"), TestMethod]
        public void TestConstantShiftExpressions()
        {
            int bufferLen = 1000;
            StringBuilder errMsg = new StringBuilder(bufferLen);
            try
            {
                Boolean result = Test_OptimizeConstantShiftExpressions(errMsg);
                Assert.IsTrue(result);
            }
            catch (AssertFailedException e)
            {
                AssertFailedException exp = new AssertFailedException(errMsg.ToString(), e);
                throw exp;
            }
        }

        [TestCategory("Unit Tests"), TestMethod]
        public void TestConstantBoolExpressions()
        {
            int bufferLen = 1000;
            StringBuilder errMsg = new StringBuilder(bufferLen);
            try
            {
                Boolean result = Test_OptimizeConstantBoolExpressions(errMsg);
                Assert.IsTrue(result);
            }
            catch (AssertFailedException e)
            {
                AssertFailedException exp = new AssertFailedException(errMsg.ToString(), e);
                throw exp;
            }
        }

        [TestCategory("Unit Tests"), TestMethod]
        public void TestConstantUnaryExpressions()
        {
            int bufferLen = 1000;
            StringBuilder errMsg = new StringBuilder(bufferLen);
            try
            {
                Boolean result = Test_OptimizeConstantUnaryExpressions(errMsg);
                Assert.IsTrue(result);
            }
            catch (AssertFailedException e)
            {
                AssertFailedException exp = new AssertFailedException(errMsg.ToString(), e);
                throw exp;
            }
        }

        [TestCategory("Unit Tests"), TestMethod]
        public void TestStackOperations()
        {
            int bufferLen = 1000;
            StringBuilder errMsg = new StringBuilder(bufferLen);
            try
            {
                Boolean result = Test_OptimizeStackOperations(errMsg);
                Assert.IsTrue(result);
            }
            catch (AssertFailedException e)
            {
                AssertFailedException exp = new AssertFailedException(errMsg.ToString(), e);
                throw exp;
            }
        }
        
    }

    [TestClass]
    public class CompilerIntegrationTest
    {
        [DllImport("minic.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        internal static extern void Test_CompileCode(String fileName, int fileLength, StringBuilder translatedAsm);

        public CompilerIntegrationTest()
        {

        }

        [TestCategory("Integration Tests"), TestMethod()]
        public void AbsTest()
        {
            TestCompilation("AbsTest.c", "AbsTest.testc", true);
        }

        [TestCategory("Integration Tests"), TestMethod()]
        public void SimpleTest()
        {
            TestCompilation("SimpleTest.c", "SimpleTest.testc", true);
        }

        [TestCategory("Integration Tests"), TestMethod()]
        public void EuclidsTest()
        {
            TestCompilation("Euclids.c", "Euclids.testc", true);
        }

        [TestCategory("Integration Tests"), TestMethod()]
        public void MathematicalTest()
        {
            TestCompilation("MathematicalTest.c", "MathematicalTest.testc", true);
        }

        [TestCategory("Integration Tests"), TestMethod()]
        public void StackArrayTest()
        {
            TestCompilation("StackArrayTest.c", "StackArrayTest.testc", true);
        }

        [TestCategory("Integration Tests"), TestMethod()]
        public void FuncDeclTest()
        {
            TestCompilation("FuncDeclTest.c", "FuncDeclTest.testc", true);
        }

        [TestCategory("Integration Tests"), TestMethod()]
        public void ReferenceTest()
        {
            TestCompilation("ReferenceTest.c", "ReferenceTest.testc", true);
        }

        [TestCategory("Integration Tests"), TestMethod()]
        public void VarLenFuncsTest()
        {
            TestCompilation("TestVarLenFuncs.c", "TestVarLenFuncs.testc", true);
        }

        [TestCategory("Integration Tests"), TestMethod()]
        public void SimpleStructTest()
        {
            TestCompilation("ShiftRegister.c", "ShiftRegister.testc", true);
        }

        [TestCategory("Integration Tests"), TestMethod]
        public void InterruptHandlerTest()
        {
            TestCompilation("IHTest.c", "IHTest.testc", true);
        }

        [TestCategory("Integration Tests"), TestMethod]
        public void ForLoopTest()
        {
            TestCompilation("ForLoopTest.c", "ForLoopTest.testc", true);
        }

        internal void TestCompilation(String fileName, String testFileName, bool expectedPass)
        {
            FileInfo fi = new FileInfo(fileName);
            FileInfo fi2 = new FileInfo(testFileName);
            if (fi.Exists)
            {
                StringBuilder translatedCode = new StringBuilder((int)fi2.Length*5 + 1);
                int numErrors = 1;
                Test_CompileCode(fileName, (int)fi2.Length*5 + 1, translatedCode);
                if (expectedPass)
                {
                    TextReader tr = new StreamReader(testFileName);
                    String testFileOut = tr.ReadToEnd();
                    tr.Close();
                    //Needed since output will only have new lines, and not carriage returns.
                    translatedCode.Replace("\n", "\r\n");
                    if (!testFileOut.Equals(translatedCode.ToString()))
                    {
                        TextWriter tw = new StreamWriter(fileName.Replace(".c", ".failedc"));
                        tw.Write(translatedCode);
                        tw.Close();
                    }
                    Assert.AreEqual(testFileOut, translatedCode.ToString());
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

    [TestClass]
    public class CompilerSwitchStatementTest
    {
        [DllImport("minic.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl, SetLastError = false)]
        [return: MarshalAs(UnmanagedType.I1)]
        internal static extern Boolean Test_SwitchStatement_TypeCheck(StringBuilder errMsg);

        [DllImport("minic.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl, SetLastError = false)]
        [return: MarshalAs(UnmanagedType.I1)]
        internal static extern Boolean Test_SwitchStatementWithDefault_FGGen(StringBuilder errMsg);

        [DllImport("minic.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl, SetLastError = false)]
        [return: MarshalAs(UnmanagedType.I1)]
        internal static extern Boolean Test_SwitchStatement_FGGen(StringBuilder errMsg);

        [DllImport("minic.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl, SetLastError = false)]
        [return: MarshalAs(UnmanagedType.I1)]
        internal static extern Boolean Test_OptimizeConstantSwitchStatements(StringBuilder errMsg);

        [DllImport("minic.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl, SetLastError = false)]
        [return: MarshalAs(UnmanagedType.I1)]
        internal static extern Boolean Test_OptimizeVariableSwitchStatements(StringBuilder errMsg);

        [DllImport("minic.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl, SetLastError = false)]
        [return: MarshalAs(UnmanagedType.I1)]
        internal static extern Boolean Test_OptimizeConstantDefaultSwitchStatements(StringBuilder errMsg);
        
        [DllImport("minic.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl, SetLastError = false)]
        [return: MarshalAs(UnmanagedType.I1)]
        internal static extern Boolean Test_OptimizeConstantNoDefaultSwitchStatements(StringBuilder errMsg);
        
        public CompilerSwitchStatementTest()
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
        // [TestInitialize()]
        // public void MyTestInitialize() { }
        //
        // Use TestCleanup to run code after each test has run
        // [TestCleanup()]
        // public void MyTestCleanup() { }
        //
        #endregion

        [TestCategory("Unit Tests"), TestMethod]
        public void TestSwitchStatement_TypeCheck()
        {
            int bufferLen = 1000;
            StringBuilder errMsg = new StringBuilder(bufferLen);
            try
            {
                Boolean result = Test_SwitchStatement_TypeCheck(errMsg);
                Assert.IsTrue(result);
            }
            catch (AssertFailedException e)
            {
                AssertFailedException exp = new AssertFailedException(errMsg.ToString(), e);
                throw exp;
            }
        }

        [TestCategory("Unit Tests"), TestMethod]
        public void TestSwitchStatementWithDefault_FGGen()
        {
            int bufferLen = 1000;
            StringBuilder errMsg = new StringBuilder(bufferLen);
            try
            {
                Boolean result = Test_SwitchStatementWithDefault_FGGen(errMsg);
                Assert.IsTrue(result);
            }
            catch (AssertFailedException e)
            {
                AssertFailedException exp = new AssertFailedException(errMsg.ToString(), e);
                throw exp;
            }
        }

        [TestCategory("Unit Tests"), TestMethod]
        public void TestSwitchStatementWithoutDefault_FGGen()
        {
            int bufferLen = 1000;
            StringBuilder errMsg = new StringBuilder(bufferLen);
            try
            {
                Boolean result = Test_SwitchStatement_FGGen(errMsg);
                Assert.IsTrue(result);
            }
            catch (AssertFailedException e)
            {
                AssertFailedException exp = new AssertFailedException(errMsg.ToString(), e);
                throw exp;
            }
        }

        [TestCategory("Unit Tests"), TestMethod]
        public void TestOptimizeConstantSwitchStatement()
        {
            int bufferLen = 1000;
            StringBuilder errMsg = new StringBuilder(bufferLen);
            try
            {
                Boolean result = Test_OptimizeConstantSwitchStatements(errMsg);
                Assert.IsTrue(result);
            }
            catch (AssertFailedException e)
            {
                AssertFailedException exp = new AssertFailedException(errMsg.ToString(), e);
                throw exp;
            }
        }

        [TestCategory("Unit Tests"), TestMethod]
        public void TestOptimizeVariableSwitchStatements()
        {
            int bufferLen = 1000;
            StringBuilder errMsg = new StringBuilder(bufferLen);
            try
            {
                Boolean result = Test_OptimizeVariableSwitchStatements(errMsg);
                Assert.IsTrue(result);
            }
            catch (AssertFailedException e)
            {
                AssertFailedException exp = new AssertFailedException(errMsg.ToString(), e);
                throw exp;
            }
        }

        [TestCategory("Unit Tests"), TestMethod]
        public void TestOptimizeConstantDefaultSwitchStatements()
        {
            int bufferLen = 1000;
            StringBuilder errMsg = new StringBuilder(bufferLen);
            try
            {
                Boolean result = Test_OptimizeConstantDefaultSwitchStatements(errMsg);
                Assert.IsTrue(result);
            }
            catch (AssertFailedException e)
            {
                AssertFailedException exp = new AssertFailedException(errMsg.ToString(), e);
                throw exp;
            }
        }

        [TestCategory("Unit Tests"), TestMethod]
        public void TestOptimizeConstantNoDefaultSwitchStatements()
        {
            int bufferLen = 1000;
            StringBuilder errMsg = new StringBuilder(bufferLen);
            try
            {
                Boolean result = Test_OptimizeConstantNoDefaultSwitchStatements(errMsg);
                Assert.IsTrue(result);
            }
            catch (AssertFailedException e)
            {
                AssertFailedException exp = new AssertFailedException(errMsg.ToString(), e);
                throw exp;
            }
        }
    }
    
    [TestClass]
    public class CompilerTypeCheckingTest
    {
        [DllImport("minic.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl, SetLastError = false)]
        [return: MarshalAs(UnmanagedType.I1)]
        internal static extern Boolean Test_ValidType_TypeCheck(StringBuilder errMsg);
        
        [DllImport("minic.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl, SetLastError = false)]
        [return: MarshalAs(UnmanagedType.I1)]
        internal static extern Boolean Test_PrimitiveAssign_TypeCheck(StringBuilder errMsg);
        
        public CompilerTypeCheckingTest()
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
        // [TestInitialize()]
        // public void MyTestInitialize() { }
        //
        // Use TestCleanup to run code after each test has run
        // [TestCleanup()]
        // public void MyTestCleanup() { }
        //
        #endregion


        [TestCategory("Unit Tests"), TestMethod]
        public void TestInvalidTypes()
        {
            int bufferLen = 1000;
            StringBuilder errMsg = new StringBuilder(bufferLen);
            try
            {
                Boolean result = Test_ValidType_TypeCheck(errMsg);
                Assert.IsTrue(result);
            }
            catch (AssertFailedException e)
            {
                AssertFailedException exp = new AssertFailedException(errMsg.ToString(), e);
                throw exp;
            }
        }

        [TestCategory("Unit Tests"), TestMethod]
        public void TestPrimitiveAssign()
        {
            int bufferLen = 1000;
            StringBuilder errMsg = new StringBuilder(bufferLen);
            try
            {
                Boolean result = Test_PrimitiveAssign_TypeCheck(errMsg);
                Assert.IsTrue(result);
            }
            catch (AssertFailedException e)
            {
                AssertFailedException exp = new AssertFailedException(errMsg.ToString(), e);
                throw exp;
            }
        }
    }

    [TestClass]
    public class CompilerStructsTest
    {
        [DllImport("minic.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl, SetLastError = false)]
        [return: MarshalAs(UnmanagedType.I1)]
        internal static extern Boolean Test_StructSymbolTableFunctions(StringBuilder errMsg);
        
        [DllImport("minic.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl, SetLastError = false)]
        [return: MarshalAs(UnmanagedType.I1)]
        internal static extern Boolean Test_StructDecl_TypeCheck(StringBuilder errMsg);

        [DllImport("minic.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl, SetLastError = false)]
        [return: MarshalAs(UnmanagedType.I1)]
        internal static extern Boolean Test_StructInit_TypeCheck(StringBuilder errMsg);

        [DllImport("minic.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl, SetLastError = false)]
        [return: MarshalAs(UnmanagedType.I1)]
        internal static extern Boolean Test_StructDeclInit_TypeCheck(StringBuilder errMsg);

        [DllImport("minic.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl, SetLastError = false)]
        [return: MarshalAs(UnmanagedType.I1)]
        internal static extern Boolean Test_StructInit_FGGen(StringBuilder errMsg);

        [DllImport("minic.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl, SetLastError = false)]
        [return: MarshalAs(UnmanagedType.I1)]
        internal static extern Boolean Test_StructDeclInit_FGGen(StringBuilder errMsg);

        [DllImport("minic.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl, SetLastError = false)]
        [return: MarshalAs(UnmanagedType.I1)]
        internal static extern Boolean Test_StructReference_TypeCheck(StringBuilder errMsg);

        [DllImport("minic.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl, SetLastError = false)]
        [return: MarshalAs(UnmanagedType.I1)]
        internal static extern Boolean Test_StructArrowReference_TypeCheck(StringBuilder errMsg);

        [DllImport("minic.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl, SetLastError = false)]
        [return: MarshalAs(UnmanagedType.I1)]
        internal static extern Boolean Test_StructReference_FGGen(StringBuilder errMsg);

        [DllImport("minic.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl, SetLastError = false)]
        [return: MarshalAs(UnmanagedType.I1)]
        internal static extern Boolean Test_StructArrowReference_FGGen(StringBuilder errMsg);


        public CompilerStructsTest()
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
        // [TestInitialize()]
        // public void MyTestInitialize() { }
        //
        // Use TestCleanup to run code after each test has run
        // [TestCleanup()]
        // public void MyTestCleanup() { }
        //
        #endregion


        [TestCategory("Unit Tests"), TestMethod]
        public void TestStructSymbolTableFunctions()
        {
            int bufferLen = 1000;
            StringBuilder errMsg = new StringBuilder(bufferLen);
            try
            {
                Boolean result = Test_StructSymbolTableFunctions(errMsg);
                Assert.IsTrue(result);
            }
            catch (AssertFailedException e)
            {
                AssertFailedException exp = new AssertFailedException(errMsg.ToString(), e);
                throw exp;
            }
        }

        [TestCategory("Unit Tests"), TestMethod]
        public void TestStructDecl_TypeCheck()
        {
            int bufferLen = 1000;
            StringBuilder errMsg = new StringBuilder(bufferLen);
            try
            {
                Boolean result = Test_StructDecl_TypeCheck(errMsg);
                Assert.IsTrue(result);
            }
            catch (AssertFailedException e)
            {
                AssertFailedException exp = new AssertFailedException(errMsg.ToString(), e);
                throw exp;
            }
        }

        [TestCategory("Unit Tests"), TestMethod]
        public void TestStructInit_TypeCheck()
        {
            int bufferLen = 1000;
            StringBuilder errMsg = new StringBuilder(bufferLen);
            try
            {
                Boolean result = Test_StructInit_TypeCheck(errMsg);
                Assert.IsTrue(result);
            }
            catch (AssertFailedException e)
            {
                AssertFailedException exp = new AssertFailedException(errMsg.ToString(), e);
                throw exp;
            }
        }

        [TestCategory("Unit Tests"), TestMethod]
        public void TestStructDeclInit_TypeCheck()
        {
            int bufferLen = 1000;
            StringBuilder errMsg = new StringBuilder(bufferLen);
            try
            {
                Boolean result = Test_StructDeclInit_TypeCheck(errMsg);
                Assert.IsTrue(result);
            }
            catch (AssertFailedException e)
            {
                AssertFailedException exp = new AssertFailedException(errMsg.ToString(), e);
                throw exp;
            }
        }

        [TestCategory("Unit Tests"), TestMethod]
        public void TestStructInit_FGGen()
        {
            int bufferLen = 1000;
            StringBuilder errMsg = new StringBuilder(bufferLen);
            try
            {
                Boolean result = Test_StructInit_FGGen(errMsg);
                Assert.IsTrue(result);
            }
            catch (AssertFailedException e)
            {
                AssertFailedException exp = new AssertFailedException(errMsg.ToString(), e);
                throw exp;
            }
        }

        [TestCategory("Unit Tests"), TestMethod]
        public void TestStructDeclInit_FGGen()
        {
            int bufferLen = 1000;
            StringBuilder errMsg = new StringBuilder(bufferLen);
            try
            {
                Boolean result = Test_StructDeclInit_FGGen(errMsg);
                Assert.IsTrue(result);
            }
            catch (AssertFailedException e)
            {
                AssertFailedException exp = new AssertFailedException(errMsg.ToString(), e);
                throw exp;
            }
        }

        [TestCategory("Unit Tests"), TestMethod]
        public void TestStructReference_TypeCheck()
        {
            int bufferLen = 1000;
            StringBuilder errMsg = new StringBuilder(bufferLen);
            try
            {
                Boolean result = Test_StructReference_TypeCheck(errMsg);
                Assert.IsTrue(result);
            }
            catch (AssertFailedException e)
            {
                AssertFailedException exp = new AssertFailedException(errMsg.ToString(), e);
                throw exp;
            }
        }

        [TestCategory("Unit Tests"), TestMethod]
        public void TestStructArrowReference_TypeCheck()
        {
            int bufferLen = 1000;
            StringBuilder errMsg = new StringBuilder(bufferLen);
            try
            {
                Boolean result = Test_StructArrowReference_TypeCheck(errMsg);
                Assert.IsTrue(result);
            }
            catch (AssertFailedException e)
            {
                AssertFailedException exp = new AssertFailedException(errMsg.ToString(), e);
                throw exp;
            }
        }

        [TestCategory("Unit Tests"), TestMethod]
        public void TestStructReference_FGGen()
        {
            int bufferLen = 1000;
            StringBuilder errMsg = new StringBuilder(bufferLen);
            try
            {
                Boolean result = Test_StructReference_FGGen(errMsg);
                Assert.IsTrue(result);
            }
            catch (AssertFailedException e)
            {
                AssertFailedException exp = new AssertFailedException(errMsg.ToString(), e);
                throw exp;
            }
        }

        [TestCategory("Unit Tests"), TestMethod]
        public void TestStructArrowReference_FGGen()
        {
            int bufferLen = 1000;
            StringBuilder errMsg = new StringBuilder(bufferLen);
            try
            {
                Boolean result = Test_StructArrowReference_FGGen(errMsg);
                Assert.IsTrue(result);
            }
            catch (AssertFailedException e)
            {
                AssertFailedException exp = new AssertFailedException(errMsg.ToString(), e);
                throw exp;
            }
        }
    }

}

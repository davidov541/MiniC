using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Emulator
{
    public enum Ops
	{
	    add,
        addi,
        lwn,
        swn,
        ldi,
        la,
        move,
        j,
        jal,
        beq,
        bgt,
        blt,
        bne,
        ldw,
        sdw,
        ori,
        slli,
        and,
        jr,
        neg,
        nop,
        not,
        or,
        sll,
        sub,
        ldl,
        wp,
        rp,
        disi,
        eni,
        swi,
        jalr,
        mtc0,
        mfc0
	}

    public class RegInfo
    {
        private String _name;
        public String Name
        {
            get { return _name; }
            set { _name = value; }
        }

        private Int32 _value;
        public Int32 Value
        {
            get { return _value; }
            set { _value = value; }
        }

        public String HexValue
        {
            get { return "0x" + _value.ToString("x8"); }
        }

        public RegInfo() { }

        public RegInfo(String name, Int32 val)
        {
            this._name = name;
            this._value = val;
        }
    }

    public class MemInfo
    {
        private Int32 _address;
        public Int32 Address
        {
            get { return _address; }
            set { _address = value; }
        }

        private Int16 _value;
        public Int16 Value
        {
            get { return _value; }
            set { _value = value; }
        }

        public String HexValue
        {
            get { return "0x" + _value.ToString("x4"); }
        }

        public MemInfo() { }
        public MemInfo(Int32 address, Int16 value)
        {
            this._address = address;
            this._value = value;
        }
    }

    public class PortInfo
    {
        private Int32 _address;
        public Int32 Address
        {
            get { return _address; }
            set { _address = value; }
        }

        private Int32 _value;
        public Int32 Value
        {
            get { return _value; }
            set { _value = value; }
        }

        public String HexValue
        {
            get { return "0x" + _value.ToString("x8"); }
        }

        public PortInfo() { }
        public PortInfo(Int32 address, Int16 value)
        {
            this._address = address;
            this._value = value;
        }        
    }

    public class BitEpicness
    {
        private Dictionary<String, short> _labels = new Dictionary<string, short>();
        public Dictionary<String, short> Labels
        {
            get { return _labels; }
            set { _labels = value; }
        }

        public List<Int32> RegisterValues
        {
            get
            {
                List<Int32> values = new List<Int32>();
                for (int i = 0; i < 16; i++)
                {
                    values.Add(this._reginfo[i].Value);
                }
                return values;
            }
        }
        public List<String> RegisterNames
        {
            get 
            {
                List<String> names = new List<string>();
                for (int i = 0; i < 16; i++)
                {
                    names.Add(this._reginfo[i].Name);
                }
                return names;
            }
        }

        public List<Int32> CoprocessorValues
        {
            get
            {
                List<Int32> values = new List<Int32>();
                for (int i = 16; i < this._reginfo.Count; i++)
                {
                    values.Add(this._reginfo[i].Value);
                }
                return values;
            }
        }

        public List<String> CoProcessorNames
        {
            get
            {
                List<String> names = new List<string>();
                for (int i = 16; i < this._reginfo.Count; i++)
                {
                    names.Add(this._reginfo[i].Name);
                }
                return names;
            }
        }

        private List<RegInfo> _reginfo = new List<RegInfo>();
        public List<RegInfo> RegisterInformation
        {
            get { return this._reginfo;  }
            set { this._reginfo = value; }
        }

        public List<Int16> MemoryValues
        {
            get
            {
                List<Int16> vals = new List<short>();
                foreach (MemInfo mem in this._meminfo)
                {
                    vals.Add(mem.Value);
                }
                return vals;
            }
        }

        private List<MemInfo> _meminfo = new List<MemInfo>();
        public List<MemInfo> MemoryInformation
        {
            get { return this._meminfo; }
            set { this._meminfo = value; }
        }

        public List<Int32> PortValues
        {
            get
            {
                List<Int32> vals = new List<int>();
                foreach (PortInfo port in this._portinfo)
                {
                    vals.Add(port.Value);
                }
                return vals;
            }
        }

        private List<PortInfo> _portinfo = new List<PortInfo>();
        public List<PortInfo> PortInformation
        {
            get { return _portinfo; }
            set { _portinfo = value; }
        }

        private UInt32 _pcvalue = 0;
        public UInt32 PCValue
        {
            get { return _pcvalue; }
            set { _pcvalue = value; }
        }

        private List<String> _firmware = new List<String>();
        public List<String> FirmwareValues
        {
            get { return _firmware; }
            set { _firmware = value; }
        }

        private readonly int MEMSIZE = 8388608;
        private readonly int FIRMWAREMEMSIZE = 512;

        public BitEpicness(Dictionary<String, short> labels)
        {
            this._labels = labels;
            List<String> regnames = new List<String>() { "$0", "$at", "$v", "$a", "$s0", "$s1", "$os0", "$os1", "$k0", "$k1", "$k2", "$fp", "$gp", "$sp", "$rr", "$ra" };
            List<String> c0names = new List<String>() { "$epc", "$cause", "$br", "$im", "$ostmp", "$mode" };
            for(int i = 0; i < 16; i++)
            {
                this._reginfo.Add(new RegInfo(regnames[i], 0));
            }
            for (int i = 0; i < c0names.Count; i++)
            {
                if (c0names[i].Equals("$im"))
                {
                    this._reginfo.Add(new RegInfo(c0names[i], unchecked((Int32) 0xFFFFFFFF)));
                }
                else
                {
                    this._reginfo.Add(new RegInfo(c0names[i], 0));
                }
            }
            for (int i = 0; i < MEMSIZE; i++)
            {
                this._meminfo.Add(new MemInfo(i, 0));
            }
            for (int i = 0; i < 16; i++)
            {
                this._portinfo.Add(new PortInfo(i, 0));
            }
        }

        public override string ToString()
        {
            String str = "PC = " + this._pcvalue + "\n";
            foreach (RegInfo reg in this._reginfo)
            {
                str += reg.Name + " = " + reg.Value + "\n";
            }
            foreach (PortInfo p in this._portinfo)
            {
                str += "Port #" + p.Address + " = " + p.Value + "\n";
            }
            return str;
        }

        public void Step()
        {
            if (this._pcvalue < this._firmware.Count)
            {
                this.evaluateAsmInstruction(this._firmware[(int)this._pcvalue]);
                this._pcvalue++;
            }
        }

        public void Run()
        {
            while (this._pcvalue < this._firmware.Count)
	        {
                this.Step();
	        }
        }

        public void evaluateAsmInstruction(String command)
        {
            List<String> asmParts = command.Split(' ', ',').ToList<String>();
            asmParts.RemoveAll(str => str.Equals(""));
            Ops operation;
            switch (asmParts[0])
            {
                case "add":
                    operation = Ops.add;
                    break;
                case "addi":
                    operation = Ops.addi;
                    break;
                case "lwn":
                    operation = Ops.lwn;
                    break;
                case "swn":
                    operation = Ops.swn;
                    break;
                case "ldi":
                    operation = Ops.ldi;
                    break;
                case "la":
                    operation = Ops.la;
                    break;
                case "move":
                    operation = Ops.move;
                    break;
                case "j":
                    operation = Ops.j;
                    break;
                case "jal":
                    operation = Ops.jal;
                    break;
                case "beq":
                    operation = Ops.beq;
                    break;
                case "bgt":
                    operation = Ops.bgt;
                    break;
                case "blt":
                    operation = Ops.blt;
                    break;
                case "bne":
                    operation = Ops.bne;
                    break;
                case "ldw":
                    operation = Ops.ldw;
                    break;
                case "sdw":
                    operation = Ops.sdw;
                    break;
                case "ori":
                    operation = Ops.ori;
                    break;
                case "slli":
                    operation = Ops.slli;
                    break;
                case "and":
                    operation = Ops.and;
                    break;
                case "jr":
                    operation = Ops.jr;
                    break;
                case "neg":
                    operation = Ops.neg;
                    break;
                case "nop":
                    operation = Ops.nop;
                    break;
                case "not":
                    operation = Ops.not;
                    break;
                case "or":
                    operation = Ops.or;
                    break;
                case "sll":
                    operation = Ops.sll;
                    break;
                case "sub":
                    operation = Ops.sub;
                    break;
                case "ldl":
                    operation = Ops.ldl;
                    break;
                case "wp":
                    operation = Ops.wp;
                    break;
                case "rp":
                    operation = Ops.rp;
                    break;
                case "disi":
                    operation = Ops.disi;
                    break;
                case "eni":
                    operation = Ops.eni;
                    break;
                case "swi":
                    operation = Ops.swi;
                    break;
                case "jalr":
                    operation = Ops.jalr;
                    break;
                case "mtc0":
                    operation = Ops.mtc0;
                    break;
                case "mfc0":
                    operation = Ops.mfc0;
                    break;
                default:
                    operation = Ops.add;
                    break;
            }
            asmParts.RemoveAt(0);
            this.evaluateInstruction(operation, asmParts.ToArray());
        }

        public int getRegisterNum(String regName)
        {
            return this._reginfo.FindIndex(reg => reg.Name.Equals(regName));
        }

        public void evaluateInstruction(Ops op, String[] args)
        {
            int rd, rs, rt;
            Int16 imm;
            switch (op)
            {
                case Ops.add:
                    rd = this.getRegisterNum("$rr");
                    rs = this.getRegisterNum(args[0]);
                    rt = this.getRegisterNum(args[1]);
                    this._reginfo[rd].Value = (Int32) (this._reginfo[rs].Value + this._reginfo[rt].Value);
                    break;
                case Ops.addi:
                    rd = this.getRegisterNum("$rr");
                    rs = this.getRegisterNum(args[0]);
                    imm = short.Parse(args[1]);
                    this._reginfo[rd].Value = (Int32)(this._reginfo[rs].Value + imm);
                    break;
                case Ops.lwn:
                    rd = this.getRegisterNum(args[0]);
                    rs = this.getRegisterNum(args[1]);
                    rt = this.getRegisterNum(args[2]);
                    this._reginfo[rd].Value = (Int32)this._meminfo[this._reginfo[rs].Value + this._reginfo[rt].Value].Value;
                    break;
                case Ops.swn:
                    rd = this.getRegisterNum(args[0]);
                    rs = this.getRegisterNum(args[1]);
                    rt = this.getRegisterNum(args[2]);
                    this._meminfo[this._reginfo[rs].Value + this._reginfo[rt].Value].Value = (short)this._reginfo[rd].Value;
                    break;
                case Ops.ldw:
                    rd = this.getRegisterNum(args[0]);
                    rs = this.getRegisterNum(args[1]);
                    rt = this.getRegisterNum(args[2]);
                    int firstPart = (Int32)this._meminfo[this._reginfo[rs].Value + this._reginfo[rt].Value].Value;
                    int secondPart = (Int32)this._meminfo[this._reginfo[rs].Value + this._reginfo[rt].Value + 1].Value;
                    this._reginfo[rd].Value = (firstPart << 16) + secondPart & 0x0000FFFF;
                    break;
                case Ops.sdw:
                    rd = this.getRegisterNum(args[0]);
                    rs = this.getRegisterNum(args[1]);
                    rt = this.getRegisterNum(args[2]);
                    this._meminfo[this._reginfo[rs].Value + this._reginfo[rt].Value + 1].Value = (short)(this._reginfo[rd].Value & 0x0000FFFF);
                    this._meminfo[this._reginfo[rs].Value + this._reginfo[rt].Value].Value = (short)((this._reginfo[rd].Value & 0xFFFF0000) >> 16);
                    break;
                case Ops.ldl:
                    rd = this.getRegisterNum(args[0]);
                    imm = Int16.Parse(args[1]);
                    this._reginfo[rd].Value = (Int32)imm & 0x0000FFFF;
                    break;
                case Ops.ldi:
                    rd = this.getRegisterNum(args[0]);
                    imm = Int16.Parse(args[1]);
                    this._reginfo[rd].Value = (Int32) imm;
                    break;
                case Ops.la:
                    rd = this.getRegisterNum(args[0]);
                    imm = 0;
                    foreach (var label in this._labels.Keys)
                    {
                        if (label.Equals((String)args[1]))
                        {
                            imm = this._labels[label];
                            break;
                        }
                    }
                    this._reginfo[rd].Value = imm;
                    break;
                case Ops.move:
                    rd = this.getRegisterNum(args[0]);
                    rs = this.getRegisterNum(args[1]);
                    this._reginfo[rd].Value = this._reginfo[rs].Value;
                    break;
                case Ops.ori:
                    rd = this.getRegisterNum("$rr");
                    rs = this.getRegisterNum(args[0]);
                    imm = (Int16)(Int32.Parse(args[1]) & 0x0000007F);
                    this._reginfo[rd].Value = (Int32)(this._reginfo[rs].Value | imm);
                    break;
                case Ops.slli:
                    rd = this.getRegisterNum("$rr");
                    rs = this.getRegisterNum(args[0]);
                    imm = (Int16)(Int32.Parse(args[1]) & 0x0000007F);
                    if (imm > 0)
                    {
                        this._reginfo[rd].Value = (Int32)(this._reginfo[rs].Value << imm);
                    }
                    else
                    {
                        this._reginfo[rd].Value = (Int32)(this._reginfo[rs].Value >> Math.Abs(imm));
                    }
                    break;
                case Ops.neg:
                    rd = this.getRegisterNum(args[0]);
                    rs = this.getRegisterNum(args[1]);
                    this._reginfo[rd].Value = (Int32)(this._reginfo[rs].Value * -1);
                    break;
                case Ops.not:
                    rd = this.getRegisterNum(args[0]);
                    rs = this.getRegisterNum(args[1]);
                    this._reginfo[rd].Value = (Int32)(~this._reginfo[rs].Value);
                    break;
                case Ops.sub:
                    rd = this.getRegisterNum("$rr");
                    rs = this.getRegisterNum(args[0]);
                    rt = this.getRegisterNum(args[1]);
                    this._reginfo[rd].Value = (Int32)(this._reginfo[rs].Value - this._reginfo[rt].Value);
                    break;
                case Ops.and:
                    rd = this.getRegisterNum("$rr");
                    rs = this.getRegisterNum(args[0]);
                    rt = this.getRegisterNum(args[1]);
                    this._reginfo[rd].Value = (Int32)(this._reginfo[rs].Value & this._reginfo[rt].Value);
                    break;
                case Ops.or:
                    rd = this.getRegisterNum("$rr");
                    rs = this.getRegisterNum(args[0]);
                    rt = this.getRegisterNum(args[1]);
                    this._reginfo[rd].Value = (Int32)(this._reginfo[rs].Value | this._reginfo[rt].Value);
                    break;
                case Ops.sll:
                    rd = this.getRegisterNum("$rr");
                    rs = this.getRegisterNum(args[0]);
                    rt = this.getRegisterNum(args[1]);
                    if (this._reginfo[rt].Value > 0)
                    {
                        this._reginfo[rd].Value = (Int32)(this._reginfo[rs].Value << this._reginfo[rt].Value);
                    }
                    else
                    {
                        this._reginfo[rd].Value = (Int32)(this._reginfo[rs].Value >> Math.Abs(this._reginfo[rt].Value));
                    }
                    break;
                case Ops.mtc0:
                    rd = this.getRegisterNum(args[0]);
                    rs = this.getRegisterNum(args[1]);
                    this._reginfo[rs].Value = this._reginfo[rd].Value;
                    break;
                case Ops.mfc0:
                    rd = this.getRegisterNum(args[0]);
                    rs = this.getRegisterNum(args[1]);
                    this._reginfo[rd].Value = this._reginfo[rs].Value;
                    break;
                case Ops.beq:
                    rd = this.getRegisterNum(args[0]);
                    rs = this.getRegisterNum(args[1]);
                    rt = this.getRegisterNum(args[2]);
                    if (this._reginfo[rd].Value == this._reginfo[rs].Value)
                    {
                        this._pcvalue = (uint)this._reginfo[rt].Value;
                    }
                    break;
                case Ops.bgt:
                    rd = this.getRegisterNum(args[0]);
                    rs = this.getRegisterNum(args[1]);
                    rt = this.getRegisterNum(args[2]);
                    if (this._reginfo[rd].Value > this._reginfo[rs].Value)
                    {
                        this._pcvalue = (uint)this._reginfo[rt].Value;
                    }
                    break;
                case Ops.blt:
                    rd = this.getRegisterNum(args[0]);
                    rs = this.getRegisterNum(args[1]);
                    rt = this.getRegisterNum(args[2]);
                    if (this._reginfo[rd].Value < this._reginfo[rs].Value)
                    {
                        this._pcvalue = (uint)this._reginfo[rt].Value;
                    }
                    break;
                case Ops.bne:
                    rd = this.getRegisterNum(args[0]);
                    rs = this.getRegisterNum(args[1]);
                    rt = this.getRegisterNum(args[2]);
                    if (this._reginfo[rd].Value != this._reginfo[rs].Value)
                    {
                        this._pcvalue = (uint)this._reginfo[rt].Value;
                    }
                    break;
                case Ops.jr:
                    rd = this.getRegisterNum(args[0]);
                    this._pcvalue = (uint) this._reginfo[rd].Value;
                    break;
                case Ops.jalr:
                    rs = this.getRegisterNum("$ra");
                    this._reginfo[rs].Value = (Int32) this._pcvalue;
                    rd = this.getRegisterNum(args[0]);
                    this._pcvalue = (uint)this._reginfo[rd].Value;
                    break;
                case Ops.j:
                    this._pcvalue = (uint) this._labels[args[0]];
                    break;
                case Ops.jal:
                    rs = this.getRegisterNum("$ra");
                    this._reginfo[rs].Value = (Int32)this._pcvalue + 1;
                    this._pcvalue = (uint) this._labels[args[0]];
                    break;
                case Ops.wp:
                    rd = this.getRegisterNum(args[0]);
                    this._portinfo[Int32.Parse(args[1])].Value = this._reginfo[rd].Value;
                    break;
                case Ops.rp:
                    rd = this.getRegisterNum(args[0]);
                    this._reginfo[rd].Value = this._portinfo[Int32.Parse(args[1])].Value;
                    break;
                case Ops.swi:
                case Ops.eni:
                case Ops.disi:
                case Ops.nop:
                default:
                    break;
            }
        }
    }
}

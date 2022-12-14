//  CMPE283 vmx_probe_mod.c - Kernel module for CMPE283 assignment 1

#include<linux/module.h>
#include<linux/kernel.h>
#include <asm/msr.h>  // for rdmsr()


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sai Manasa Yadlapalli, Shubhada Paithankar");
MODULE_DESCRIPTION("Kernel module that probes for VMX info");
MODULE_VERSION("0.1");

// MSR ids from SDM
#define IA32_VMX_ENTRY_CTLS		0x484
#define IA32_VMX_EXIT_CTLS		0x483
#define IA32_VMX_PINBASED_CTLS          0x481
#define IA32_VMX_PROCBASED_CTLS 	0x482
#define IA32_VMX_PROCBASED_CTLS2	0x48B
#define IA32_VMX_PROCBASED_CTLS3	0x492

// bit_info
//
// Represents a MSR's bit number, description
// Used by probe function to output info
struct bit_info {
	uint8_t bit;
	const char *name;
};


// VM entry info
struct bit_info vmentry[12] =
{
	{2, "Load debug controls"},
	{9, "IA-32e mode guest"},
	{10, "Entry to SMM"},
	{11, "Deactivate dual-monitor treatment"},
	{13, "Load IA32_PERF_GLOBAL_CTRL"},
	{14, "Load IA32_PAT"},
	{15, "Load IA32_EFER"},
	{16, "Load IA32_BNDCFGS"},
	{17, "Conceal VMX from PT"},
	{18, "Load IA32_RTIT_CTL"},
	{20, "Load CET state"},
	{22, "Load PKRS"}

};

// VM exit info
struct bit_info vmexit[14] =
{
	{2, "Save debug controls"},
	{9, "Host address-space size"},
	{12, "Load IA32_PERF_GLOBAL_CTRL"},
	{15, "Acknowledge interrupt on exit"},
	{18, "Save IA32_PAT"},
	{19, "Load IA32_PAT"},
	{20, "Save IA32_EFER"},
	{21, "Load IA32_EFER"},
	{22, "Save VMX-preemption timer value"},
	{23, "Clear IA32_BNDCFGS"},
	{24, "Conceal VMX from PT"},
	{25, "Clear IA32_RTIT_CT"},
	{28, "Load CET state"},
	{29, "Load PKRS"}

};

// VM Pinbased info
struct bit_info pinbased[5] =
{
	{ 0, "External Interrupt Exiting" },
	{ 3, "NMI Exiting" },
	{ 5, "Virtual NMIs" },
	{ 6, "Activate VMX Preemption Timer" },
	{ 7, "Process Posted Interrupts" }
};

// ProcBased controls primary
struct bit_info procprimary[22] =
{
	{ 2, "Interrupt-window exiting" },
	{ 3, "Use TSC offsetting" },
	{ 7, "HLT exiting" },
	{ 9, "INVLPG exiting" },
	{ 10, "MWAIT exitin" },
	{ 11, "RDPMC exiting"},
	{ 12, "RDTSC exiting"},
	{ 15, "CR3-load exiting"},
	{ 16, "CR3-store exiting"},
	{ 17, "Activate tertiary controls"},
	{ 19, "CR8-load exiting"},
	{ 20, "CR8-store exiting"},
	{ 21, "Use TPR shadow"},
	{ 22, "NMI-window exiting"},
	{ 23, "MOV-DR exiting"},
	{ 24, "Unconditional I/O exiting"},
	{ 25, "Use I/O bitmaps"},
	{ 27, "Monitor trap flag"},
	{ 28, "Use MSR bitmaps"},
	{ 29, "MONITOR exiting"},
	{ 30, "PAUSE exiting"},
	{ 31, "Activate secondary controls"}
};


// ProcBased controls secondary
struct bit_info procsecondry[27] =
{
	{0, "Virtualize APIC accesses"},
	{1, "Enable EPT"},
	{2, "Descriptor-table exiting"},
	{3, "Enable RDTSCP"},
	{4, "Virtualize x2APIC mode"},
	{5, "Enable VPID"},
	{6, "WBINVD exiting"},
	{7, "Unrestricted guest"},
	{8, "APIC-register virtualization"},
	{9, "Virtual-interrupt delivery"},
	{10, "PAUSE-loop exitin"},
	{11, "RDRAND exiting"},
	{12, "Enable INVPCID"},
	{13, "Enable VM functions"},
	{14, "VMCS shadowin"},
	{15, "Enable ENCLS exiting"},
	{16, "RDSEED exiting"},
	{17, "Enable PML"},
	{18, "EPT-violation #VE"},
	{19, "Conceal VMX from PT"},
	{20, "Enable XSAVES/XRSTORS"},
	{22, "Mode-based execute control for EPT"},
	{23, "Sub-page write permissions for EPT"},
	{24, "Intel PT uses guest physical addresses"},
	{25, "Use TSC scaling"},
	{26, "Enable user wait and pause"},
	{28, "Enable ENCLV exiting"}
};

// ProcBased controls tertiary
struct bit_info proctertiary[4] =
{
	{0, "LOADIWKEY execution causes VM exits"},
	{1, "Enables HLAT: Hypervisor managed linear address translation"},
	{2, "EPT paging write operation"},
	{3, "Guest-paging verification"}
};


// probe_bit_info
//
// Prints out MSR capabilities based on bit_info struct and MSR values of lo, hi
void probe_bit_info(struct bit_info *bit_info, uint8_t len, uint32_t lo, uint32_t hi)
{
	uint8_t i;
	struct bit_info *temp;

	for (i = 0; i < len; i++) {
		temp = &bit_info[i];
		printk(KERN_INFO "  %s: Can set=%s, Can clear=%s\n", temp->name, (hi & (1 << temp->bit)) ? "Yes" : "No", !(lo & (1 << temp->bit)) ? "Yes" : "No");
	}
}

// Module that probes VMX registers for info
void probe_vmx_features(void)
{
	uint32_t lo, hi;

	/* entry controls */
	rdmsr(IA32_VMX_ENTRY_CTLS, lo, hi);
	printk(KERN_INFO "VMX Entry Controls MSR: 0x%llx\n", (uint64_t)(lo | (uint64_t)hi << 32));
	probe_bit_info(vmentry, 12, lo, hi);

	/* exit controls */
	rdmsr(IA32_VMX_EXIT_CTLS, lo, hi);
	printk(KERN_INFO "VMX Exit Controls MSR: 0x%llx\n", (uint64_t)(lo | (uint64_t)hi << 32));
	probe_bit_info(vmexit, 14, lo, hi);

	/* pinbased controls */
	rdmsr(IA32_VMX_PINBASED_CTLS, lo, hi);
	printk(KERN_INFO "VMX Pinbased Controls MSR: 0x%llx\n", (uint64_t)(lo | (uint64_t)hi << 32));
	probe_bit_info(pinbased, 5, lo, hi);

	/* Procbased primary controls primary */
	rdmsr(IA32_VMX_PROCBASED_CTLS, lo, hi);
	printk(KERN_INFO "VMX Procbased primary Controls MSR: 0x%llx\n", (uint64_t)(lo | (uint64_t)hi << 32));
	probe_bit_info(procprimary, 22, lo, hi);

	/* Procbased secondary controls secondary */
	rdmsr(IA32_VMX_PROCBASED_CTLS2, lo, hi);
	printk(KERN_INFO "Procbased secondary Controls MSR: 0x%llx\n", (uint64_t)(lo | (uint64_t)hi << 32));
	probe_bit_info(procsecondry, 27, lo, hi);

	/* Procbased secondary controls tertiary */
	rdmsr(IA32_VMX_PROCBASED_CTLS3, lo, hi);
	printk(KERN_INFO "Procbased tertiary Controls MSR: 0x%llx\n", (uint64_t)(lo | (uint64_t)hi << 32));
	probe_bit_info(proctertiary, 4, lo, hi);

}

// Module Entry point
static int __init vmx_probe_mod_init(void)
{
        printk(KERN_ALERT "CMPE283-Assignment-1 vmx_probe_mod start \n");
        probe_vmx_features();
        return 0;
}


// Module Exit point
static void __exit vmx_probe_mod_exit(void)
{
        printk(KERN_ALERT "CMPE283-Assignment-1 vmx_probe_mod finish \n");
}

module_init(vmx_probe_mod_init);
module_exit(vmx_probe_mod_exit);

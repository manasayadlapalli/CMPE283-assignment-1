
# CMPE 283 Assignment-1:
## Team Members:
1. Shubadha Paithankar(SJSU ID: 016013283)
2. Sai Manasa Yadlapalli (SJSU ID: 015999659)

## Development Environment:
  1. Lenovo Ideapad Slimpro 14 laptop with Intel 11th Gen Intel(R) Core(TM) i5-11300H processor that supports VMX, VT-x,EPT and VT-d.
  2. Bare metal OS is Windows 11 with credential/device guard & virtualization based security disabled as per: https://kb.vmware.com/s/article/2146361
  3. Hypervisor is VMWare Workstation player 16.2
  4. Guest OS is Ubuntu 22.04

## Kernel-module development steps:
  1. Ubuntu 22.04 kernel version: 5.15.0-52-generic
  2. Installed kernel headers with: 
  ``` sudo apt-get install build-essential linux-headers-`uname -r` ```
  
# Questions:
## 1. Individual Contribution:

### Sai Manasa Yadlapalli:
I worked on the below three MSR’s <br>
IA32_VMX_EXIT_CTLS  <br>
IA32_VMX_ENTRY_CTLS  <br>
IA32_VMX_PROCBASED_CTLS3 

Firstly, I tested out the ‘hello world’ code on kernel module and then modified it to probe VM Entry, VM Exists. Next, I added the functionality to probe VM pin based controls. Implemented the Entry / Exit / Procbased controls. <br>

### Shubhada Paithankar:
I worked on the remaining three MSR’s <br>
IA32_VMX_PINBASED_CTLS <br>
IA32_VMX_PROCBASED_CTLS <br>
IA32_VMX_PROCBASED_CTLS2 <br>

Added the kernel module IA32_VMX_EXIT_CTLS to determine how it should set the reserved bits. Also, after that, I added IA32_VMX_ENTRY_CTLS MSR (index 484H) reports on the allowed settings of most of the VM-entry control. At the end, I modified the script with  IA32_VMX_PROCBASED_CTLS3 module to determine which bits may be set to 1. Failure to clear reserved bits causes subsequent VM entries to fail in the script.

## 2. Steps Contribution:
1) Download the VMware Workstation in your OS. 
2) After the installation, Click on ‘Create a new VM’
3) Download the Ubuntu OS Iso image for VMware Workstation
4) Choose your configuration and virtual hardware compatibility
5) Choose ‘Use iso image’ option for Operating System installation and attach the downloaded Iso image file.
6) Shut down the VM and enable Nested Virtualization.
7) Power on the VM, remove the iso image
8) Open Ubuntu command line and install current linux kernel header files 
     ``` sudo apt-get install build-essential linux-headers-`uname -r` ```
9) Install git using command line ``` sudo apt install git ```
10) To clone our working code, 
    ``` git clone https://github.com/manasayadlapalli/CMPE283-assignment-1 ```
11) ``` cd CMPE-assignment-1```, Run the Makefile with the command ``` make all ```
12) After running the Makefile, vmx_probe_mod.ko file is generated.
13) Run the command ```sudo insmod vmx_probe_mod.ko``` to insert the module into the kernel.
14) To see the output, run ```sudo dmesg```, output screenshots are attached below.
15) Lastly, remove the module from kernel using the command
      ```sudo rmmod vmx_probe_mod.ko ```


## Assignment-1 output snippets:

<img width="628" alt="Screen Shot 2022-10-25 at 3 56 08 PM" src="https://user-images.githubusercontent.com/99461999/197897398-8098d199-1986-46dd-8321-dd00ac5a7c6e.png">

<img width="628" alt="Screen Shot 2022-10-25 at 3 57 26 PM" src="https://user-images.githubusercontent.com/99461999/197897505-e05de32c-3515-403a-8b24-00fa2ae91893.png">

## References: 
1. https://www.youtube.com/watch?v=4tgluSJDA_E
2. http://retis.sssup.it/luca/KernelProgramming/Slides/modules_intro.pdf


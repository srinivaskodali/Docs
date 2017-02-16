#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

#undef unix
struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = __stringify(KBUILD_MODNAME),
 .init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
 .exit = cleanup_module,
#endif
};

static const struct modversion_info ____versions[]
__attribute_used__
__attribute__((section("__versions"))) = {
	{        0, "cleanup_module" },
	{        0, "init_module" },
	{        0, "struct_module" },
	{        0, "unregister_chrdev" },
	{        0, "register_chrdev" },
	{        0, "pci_find_device" },
	{        0, "printk" },
	{        0, "iounmap" },
	{        0, "__ioremap" },
};

static const char __module_depends[]
__attribute_used__
__attribute__((section(".modinfo"))) =
"depends=";


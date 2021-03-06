#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/device.h>

MODULE_LICENSE("GPL");

int key_match(struct device *dev, struct device_driver *drv)		//匹配函数
{
    return !strncmp(dev->kobj.name,drv->name,strlen(drv->name));	//注意.由于dev->init_name被拷到dev->kobj.name了,dev->init_name被置空
}  									//所以,使用dev->kobj.name来做比较


struct bus_type key_bus_type = {	//自定义一条bus
	.name = "key_bus",
	.match = key_match,
	};
	
EXPORT_SYMBOL(key_bus_type);		//一定要 声明可以可以给外面的函数使用

int key_bus_init(void)
{
	int ret;
	
	ret = bus_register(&key_bus_type);//分配次设备号,挂载注册一个自定义总线设备到linux上
	
	return ret;

}

void key_bus_exit(void)
{
	bus_unregister(&key_bus_type);	//卸载这个总线设备
}


module_init(key_bus_init);
module_exit(key_bus_exit);

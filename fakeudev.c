#include <dlfcn.h>
#include <libudev.h>
#include <stdio.h>

struct udev *(*orig_udev_new)(void);
struct udev *(*orig_udev_ref)(struct udev *udev);
struct udev *(*orig_udev_unref)(struct udev *udev);
int (*orig_udev_enumerate_scan_devices)(struct udev_enumerate *udev_enumerate);
int (*orig_udev_enumerate_scan_subsystems)(
    struct udev_enumerate *udev_enumerate);
struct udev_list_entry *(*orig_udev_enumerate_get_list_entry)(
    struct udev_enumerate *udev_enumerate);
int (*orig_udev_enumerate_add_syspath)(struct udev_enumerate *udev_enumerate,
                                       const char *syspath);
struct udev *(*orig_udev_enumerate_get_udev)(
    struct udev_enumerate *udev_enumerate);
struct udev_enumerate *(*orig_udev_enumerate_new)(struct udev *udev);
struct udev_enumerate *(*orig_udev_enumerate_unref)(
    struct udev_enumerate *udev_enumerate);
const char *(*orig_udev_device_get_devpath)(struct udev_device *udev_device);
const char *(*orig_udev_device_get_subsystem)(struct udev_device *udev_device);
const char *(*orig_udev_device_get_devtype)(struct udev_device *udev_device);
const char *(*orig_udev_device_get_syspath)(struct udev_device *udev_device);
const char *(*orig_udev_device_get_sysname)(struct udev_device *udev_device);
const char *(*orig_udev_device_get_sysnum)(struct udev_device *udev_device);
const char *(*orig_udev_device_get_devnode)(struct udev_device *udev_device);
struct udev_device *(*orig_udev_device_new_from_syspath)(struct udev *udev,
                                                         const char *syspath);
struct udev_device *(*orig_udev_device_unref)(struct udev_device *udev_device);
struct udev_list_entry *(*orig_udev_list_entry_get_next)(
    struct udev_list_entry *list_entry);
const char *(*orig_udev_list_entry_get_name)(
    struct udev_list_entry *list_entry);
const char *(*orig_udev_list_entry_get_value)(
    struct udev_list_entry *list_entry);
struct udev_list_entry *(*orig_udev_device_get_properties_list_entry)(
    struct udev_device *udev_device);
struct udev_list_entry *(*orig_udev_device_get_devlinks_list_entry)(
    struct udev_device *udev_device);

int (*orig_udev_enumerate_add_match_subsystem)(
    struct udev_enumerate *udev_enumerate, const char *subsystem);
struct udev_device *(*orig_udev_device_get_parent_with_subsystem_devtype)(
    struct udev_device *udev_device, const char *subsystem,
    const char *devtype);
const char *(*orig_udev_device_get_sysattr_value)(
    struct udev_device *udev_device, const char *sysattr);

struct udev *(*orig_udev_device_get_udev)(struct udev_device *udev_device);
struct udev_device *(*orig_udev_device_get_parent)(
    struct udev_device *udev_device);
struct udev_device *(*orig_udev_device_ref)(struct udev_device *udev_device);
const char *(*orig_udev_device_get_driver)(struct udev_device *udev_device);
const char *(*orig_udev_device_get_property_value)(
    struct udev_device *udev_device, const char *key);

// --

#define LOG_FILE "/root/fakeudev/fakeudev.log"
#define ORIG_LIB "/usr/lib/x86_64-linux-gnu/libudev.so.1.6.17.orig"

static void xlog(const char *fmt, ...) {
    if (0) {
        va_list args;
        va_start(args, fmt);
        FILE *fp = fopen(LOG_FILE, "a");
        if (fp == NULL)
            return;
        vfprintf(fp, fmt, args);
        fprintf(fp, "\n");
        va_end(args);
        fclose(fp);
    }
}

static void *handle;

static void *get_symbol(const char *symbol) {
    if (handle == NULL) {
        handle = dlopen(ORIG_LIB, RTLD_NOW);
        if (handle == NULL) {
            xlog("could not open original libudev %s", ORIG_LIB);
            return 0;
        }
    }
    void *sym = dlsym(handle, symbol);
    if (sym == NULL) {
        xlog("could not get symbol %s", symbol);
        return 0;
    }
    return sym;
}

struct udev *udev_new(void) {
    xlog(__FUNCTION__);
    orig_udev_new = get_symbol(__FUNCTION__);
    return (*orig_udev_new)();
}

struct udev *udev_ref(struct udev *udev) {
    xlog(__FUNCTION__);
    orig_udev_ref = get_symbol(__FUNCTION__);
    return (*orig_udev_ref)(udev);
}

struct udev *udev_unref(struct udev *udev) {
    xlog(__FUNCTION__);
    orig_udev_unref = get_symbol(__FUNCTION__);
    return (*orig_udev_unref)(udev);
}

int udev_enumerate_scan_devices(struct udev_enumerate *udev_enumerate) {
    xlog(__FUNCTION__);
    orig_udev_enumerate_scan_devices = get_symbol(__FUNCTION__);
    return (*orig_udev_enumerate_scan_devices)(udev_enumerate);
}

int udev_enumerate_scan_subsystems(struct udev_enumerate *udev_enumerate) {
    xlog(__FUNCTION__);
    orig_udev_enumerate_scan_subsystems = get_symbol(__FUNCTION__);
    return (*orig_udev_enumerate_scan_subsystems)(udev_enumerate);
}

struct udev_list_entry *
udev_enumerate_get_list_entry(struct udev_enumerate *udev_enumerate) {
    xlog(__FUNCTION__);
    orig_udev_enumerate_get_list_entry = get_symbol(__FUNCTION__);
    return (*orig_udev_enumerate_get_list_entry)(udev_enumerate);
}

int udev_enumerate_add_syspath(struct udev_enumerate *udev_enumerate,
                               const char *syspath) {
    xlog(__FUNCTION__);
    orig_udev_enumerate_add_syspath = get_symbol(__FUNCTION__);
    return orig_udev_enumerate_add_syspath(udev_enumerate, syspath);
}

struct udev *udev_enumerate_get_udev(struct udev_enumerate *udev_enumerate) {
    xlog(__FUNCTION__);
    orig_udev_enumerate_get_udev = get_symbol(__FUNCTION__);
    return (*orig_udev_enumerate_get_udev)(udev_enumerate);
}

struct udev_enumerate *udev_enumerate_new(struct udev *udev) {
    xlog(__FUNCTION__);
    orig_udev_enumerate_new = get_symbol(__FUNCTION__);
    return (*orig_udev_enumerate_new)(udev);
}

struct udev_enumerate *
udev_enumerate_unref(struct udev_enumerate *udev_enumerate) {
    xlog(__FUNCTION__);
    orig_udev_enumerate_unref = get_symbol(__FUNCTION__);
    return (*orig_udev_enumerate_unref)(udev_enumerate);
}

const char *udev_device_get_devpath(struct udev_device *udev_device) {
    xlog(__FUNCTION__);
    orig_udev_device_get_devpath = get_symbol(__FUNCTION__);
    return (*orig_udev_device_get_devpath)(udev_device);
}

const char *udev_device_get_subsystem(struct udev_device *udev_device) {
    xlog(__FUNCTION__);
    orig_udev_device_get_subsystem = get_symbol(__FUNCTION__);
    return (*orig_udev_device_get_subsystem)(udev_device);
}

const char *udev_device_get_devtype(struct udev_device *udev_device) {
    xlog(__FUNCTION__);
    orig_udev_device_get_devtype = get_symbol(__FUNCTION__);
    return (*orig_udev_device_get_devtype)(udev_device);
}

const char *udev_device_get_syspath(struct udev_device *udev_device) {
    xlog(__FUNCTION__);
    orig_udev_device_get_syspath = get_symbol(__FUNCTION__);
    return (*orig_udev_device_get_syspath)(udev_device);
}

const char *udev_device_get_sysname(struct udev_device *udev_device) {
    xlog(__FUNCTION__);
    orig_udev_device_get_sysname = get_symbol(__FUNCTION__);
    return (*orig_udev_device_get_sysname)(udev_device);
}

const char *udev_device_get_sysnum(struct udev_device *udev_device) {
    xlog(__FUNCTION__);
    orig_udev_device_get_sysnum = get_symbol(__FUNCTION__);
    return (*orig_udev_device_get_sysnum)(udev_device);
}

const char *udev_device_get_devnode(struct udev_device *udev_device) {
    xlog(__FUNCTION__);
    orig_udev_device_get_devnode = get_symbol(__FUNCTION__);
    return (*orig_udev_device_get_devnode)(udev_device);
}

struct udev_device *udev_device_new_from_syspath(struct udev *udev,
                                                 const char *syspath) {
    xlog(__FUNCTION__);
    orig_udev_device_new_from_syspath = get_symbol(__FUNCTION__);
    return (*orig_udev_device_new_from_syspath)(udev, syspath);
}

struct udev_device *udev_device_unref(struct udev_device *udev_device) {
    xlog(__FUNCTION__);
    orig_udev_device_unref = get_symbol(__FUNCTION__);
    return (*orig_udev_device_unref)(udev_device);
}

struct udev_list_entry *
udev_list_entry_get_next(struct udev_list_entry *list_entry) {
    xlog(__FUNCTION__);
    orig_udev_list_entry_get_next = get_symbol(__FUNCTION__);
    return (*orig_udev_list_entry_get_next)(list_entry);
}

const char *udev_list_entry_get_name(struct udev_list_entry *list_entry) {
    xlog(__FUNCTION__);
    orig_udev_list_entry_get_name = get_symbol(__FUNCTION__);
    return (*orig_udev_list_entry_get_name)(list_entry);
}

const char *udev_list_entry_get_value(struct udev_list_entry *list_entry) {
    xlog(__FUNCTION__);
    orig_udev_list_entry_get_value = get_symbol(__FUNCTION__);
    return (*orig_udev_list_entry_get_value)(list_entry);
}

struct udev_list_entry *
udev_device_get_properties_list_entry(struct udev_device *udev_device) {
    xlog(__FUNCTION__);
    orig_udev_device_get_properties_list_entry = get_symbol(__FUNCTION__);
    return (*orig_udev_device_get_properties_list_entry)(udev_device);
}

struct udev_list_entry *
udev_device_get_devlinks_list_entry(struct udev_device *udev_device) {
    xlog(__FUNCTION__);
    orig_udev_device_get_devlinks_list_entry = get_symbol(__FUNCTION__);
    return (*orig_udev_device_get_devlinks_list_entry)(udev_device);
}

// --

int udev_enumerate_add_match_subsystem(struct udev_enumerate *udev_enumerate,
                                       const char *subsystem) {
    xlog(__FUNCTION__);
    orig_udev_enumerate_add_match_subsystem = get_symbol(__FUNCTION__);
    return (*orig_udev_enumerate_add_match_subsystem)(udev_enumerate,
                                                      subsystem);
}

struct udev_device *
udev_device_get_parent_with_subsystem_devtype(struct udev_device *udev_device,
                                              const char *subsystem,
                                              const char *devtype) {
    xlog(__FUNCTION__);
    orig_udev_device_get_parent_with_subsystem_devtype =
        get_symbol(__FUNCTION__);
    return (*orig_udev_device_get_parent_with_subsystem_devtype)(
        udev_device, subsystem, devtype);
}

const char *udev_device_get_sysattr_value(struct udev_device *udev_device,
                                          const char *sysattr) {
    xlog(__FUNCTION__);
    orig_udev_device_get_sysattr_value = get_symbol(__FUNCTION__);
    return (*orig_udev_device_get_sysattr_value)(udev_device, sysattr);
}

struct udev *udev_device_get_udev(struct udev_device *udev_device) {
    xlog(__FUNCTION__);
    orig_udev_device_get_udev = get_symbol(__FUNCTION__);
    return (*orig_udev_device_get_udev)(udev_device);
}

struct udev_device *udev_device_get_parent(struct udev_device *udev_device) {
    xlog(__FUNCTION__);
    orig_udev_device_get_parent = get_symbol(__FUNCTION__);
    return (*udev_device_get_parent)(udev_device);
}

struct udev_device *udev_device_ref(struct udev_device *udev_device) {
    xlog(__FUNCTION__);
    orig_udev_device_ref = get_symbol(__FUNCTION__);
    return (*orig_udev_device_ref)(udev_device);
}

const char *udev_device_get_driver(struct udev_device *udev_device) {
    xlog(__FUNCTION__);
    orig_udev_device_get_driver = get_symbol(__FUNCTION__);
    return (*orig_udev_device_get_driver)(udev_device);
}

const char *udev_device_get_property_value(struct udev_device *udev_device,
                                           const char *key) {
    xlog(__FUNCTION__);
    orig_udev_device_get_property_value = get_symbol(__FUNCTION__);
    return (*orig_udev_device_get_property_value)(udev_device, key);
}

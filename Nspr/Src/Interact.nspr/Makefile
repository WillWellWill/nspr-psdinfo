
SRC_TOP = $(shell pwd)/../../
TARGET := interact_client
MK_FILENAME := Interact.mk
OBJ_DIR_NAME := interactobj

include $(SRC_TOP)/../Build/Define.mk
include $(BUILD_DIR)/NgxDefine.mk
include $(BUILD_DIR)/Objects.mk

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ -Wl,--start-group $(OBJS) $(LIBS) -Wl,--end-group

$(OBJ_TOP_DIR)/%.o: %.cpp
	$(CC) $(CPPFLAGS) $(SOFLAGS) -MM -MT $@ -MF $(patsubst %.o,%.d,$@) $<
	$(CC) $(CPPFLAGS) $(SOFLAGS) -MD -o $@ -c $<

DEPS := $(OBJS:.o=.d)
-include $(DEPS)

clean:
	rm -rf $(OBJ_TOP_DIR) $(TARGET) $(TEST)


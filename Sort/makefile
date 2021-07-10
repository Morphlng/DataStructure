CC=g++

CPPFLAGS:='-std=c++14'

ENCODING:='-fexec-charset=GBK'

sources:=$(wildcard *.c) $(wildcard *.cpp)

objects:=$(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(sources)))

dependence:=$(objects:.o=.d)

main:$(objects)
	$(CC) $(ENCODING) $(CPPFLAGS) $^ -o $@
	@./$@

%.o:%.c
	$(CC) $(ENCODING) $(CPPFLAGS) -c $< -o $@

%.o:%.cpp
	$(CC) $(ENCODING) $(CPPFLAGS) -c $< -o $@

include $(dependence)

define gen_dep
set -e; rm -f $@; \
$(CC) -MM $(CPPFLAGS) $< > $@.$$$$; \
sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
rm -f $@.$$$$
endef

%.d:%.c
	$(gen_dep)

%.d:%.cpp
	$(gen_dep)

.PHONY: clean
clean:
	rm -f $(objects) $(dependence)

cleanall:
	rm -f main $(objects) $(dependence)

echo:
	@echo sources=$(sources)
	@echo objects=$(objects)
	@echo dependence=$(dependence)
	@echo CPPFLAGS=$(CPPFLAGS)


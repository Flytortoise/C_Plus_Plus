include scripts/Makefile

.PHONY : all mm mc clean

all : $(Target)

mm:
	cd main && $(MAKE)
	cd Init && $(MAKE)
	cd Abstract && $(MAKE)
	cd Data && $(MAKE)
	cd my_stock && $(MAKE)
	cd Start && $(MAKE)
	cd Pass && $(MAKE)
	cd my_scanf && $(MAKE)
	cd interface && $(MAKE)
	cd Select_func && $(MAKE)
	cd func/Look && $(MAKE)
	cd func/Chat && $(MAKE)

mc:
	cd main && $(MAKE) clean
	cd Init && $(MAKE) clean
	cd Abstract && $(MAKE) clean
	cd Data && $(MAKE) clean
	cd my_stock && $(MAKE) clean
	cd Start && $(MAKE) clean
	cd Pass && $(MAKE) clean
	cd my_scanf && $(MAKE) clean
	cd interface && $(MAKE) clean
	cd Select_func && $(MAKE) clean
	cd func/Look && $(MAKE) clean
	cd func/Chat && $(MAKE) clean

$(Target) : mm
	@$(CC) -o $(Target) $(Allobjs) -lpthread -lsqlite3

clean : mc
	@rm -rf $(Targer) client


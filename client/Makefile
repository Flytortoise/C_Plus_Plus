include scripts/Makefile

.PHONY : all mm mc clean

all : $(Target)

mm:
	cd main && $(MAKE)
	cd Init && $(MAKE)
	cd my_stock && $(MAKE)
	cd Start && $(MAKE)
mc:
	cd main && $(MAKE) clean
	cd Init && $(MAKE) clean
	cd my_stock && $(MAKE) clean
	cd Start && $(MAKE) clean

$(Target) : mm
	@$(CC) -o $(Target) $(Allobjs) -lpthread -lsqlite3

clean : mc
	@rm -rf $(Targer) client


all:
	$(MAKE) -C lib
	$(MAKE) -C tests

.PHONY: clean
clean:
	$(MAKE) clean -C lib
	$(MAKE) clean -C tests

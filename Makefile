all:
	clang -framework Foundation -framework IOBluetooth -o blueutil blueutil.c

install: all
	cp -r blueutil /usr/local/bin

clean:
	rm -f $(OBJS) $(OUT)

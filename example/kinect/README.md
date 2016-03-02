# helloworld

this example shows the usage of `QHttp` as an HTTP server or a client. you can try this by TCP socket or unix (local) sockets.

##usage

```bash
$> ./helloworld -h
```

```text
Usage: ./helloworld [options] mode
a Hello World sample for http client and server.

Options:
  -h, --help            Displays this help.
  -v, --version         Displays version information.
  -b, --backend <type>  backend type of HTTP. could be 'tcp' or 'local',
                        default: tcp
  -p, --port <number>   tcp listening port, default: 8080

Arguments:
  mode                  working mode, client or server. default: server
```

##TCP sockets

###tcp server
to test `QHttp` server classes, start `helloworld` in server mode:
```bash
$> ./helloworld server -p 7000
```
now the server is listening on `address=QHostAddress::Any`, `port=7000` (press `ctrl+c` to stop the server).

<br/>
then test the server by pointing your browser to [localhost:7000](localhost:7000) or try any other HTTP client app:
```bash
$> curl localhost:7000
```
you shall see the `Hello World!` message from the server.


###tcp client
the simple client mode tries to fetch the weather information from [openweathermap.org](openweathermap.org):
```bash
$> ./helloworld client
```
you shall see the headers:
```
access-control-allow-credentials : true
access-control-allow-methods : get, post
transfer-encoding : chunked
server : nginx
content-type : text/xml; charset=utf-8
access-control-allow-origin : *
date : sun, 20 jul 2014 09:21:19 gmt
connection : close
x-source : redis
```


and XML body as:
```xml
<?xml version="1.0" encoding="utf-8"?>
<current>
  <city id="112931" name="Tehran">
    <coord lon="51.42" lat="35.69"/>
    <country>IR</country>
    <sun rise="2014-07-20T01:33:35" set="2014-07-20T15:47:49"/>
  </city>
  <temperature value="38" min="38" max="38" unit="celsius"/>
  <humidity value="8" unit="%"/>
  <pressure value="1006" unit="hPa"/>
  <wind>
    <speed value="6.2" name="Moderate breeze"/>
    <direction value="140" code="SE" name="SouthEast"/>
  </wind>
  <clouds value="20" name="few clouds"/>
  <visibility/>
  <precipitation mode="no"/>
  <weather number="801" value="few clouds" icon="02d"/>
  <lastupdate value="2014-07-20T09:00:00"/>
</current>
```

##Unix socket
to test unix (local) sockets as backend, use `-b local` option.

##local server
do:
```bash
$> ./helloworld server -b local
```
now the HTTP server listens on `/tmp/helloworld.socket` and says `Hello World!` to connected clients as:


###local client
do:
```bash
$> ./helloworld client -b local
```

now you shall see the server message and HTTP headers.
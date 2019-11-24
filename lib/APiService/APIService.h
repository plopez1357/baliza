#ifndef APIService_h
#define APIService_h

#include <Arduino.h>
#include <FS.h>

const char INDEX_HTML[] PROGMEM = R"rawliteral(
    <!DOCTYPE html>
        <html>
        <style>
        input[type=text], select {
        width: 100%;
        padding: 12px 20px;
        margin: 8px 0;
        display: inline-block;
        border: 1px solid #ccc;
        border-radius: 4px;
        box-sizing: border-box;
        }

        input[type=submit] {
        width: 100%;
        background-color: #4CAF50;
        color: white;
        padding: 14px 20px;
        margin: 8px 0;
        border: none;
        border-radius: 4px;
        cursor: pointer;
        }

        input[type=submit]:hover {
        background-color: #45a049;
        }

        div {
        border-radius: 5px;
        background-color: #f2f2f2;
        padding: 20px;
        }
        </style>
        <body>

        <h3>Ingrese URL y token de Travis</h3>
        
        <script>
            function c(l){document.getElementById('urlId').value=l.innerText||l.textContent;document.getElementById('tokenId').value=l.innerText||l.textContent;}
        </script>
        
        <div>
        <form method="get" action="/get">
            <label for="url">URL</label>
            <input type="text" id="urlId" name="inputUrl" placeholder="Ingrese URL" required>

            <label for="token">Token</label>
            <input type="text" id="tokenId" name="inputToken" placeholder="Ingrese token" required>
        
            <input type="submit" value="Submit" onclick="submitMessage()">
        </form>
        </div></body></html>)rawliteral";

const char SAVE_HTML[] PROGMEM = R"rawliteral(<!DOCTYPE html><html><body><h3>Credenciales guardadas</h3></div></body></html>)rawliteral";

class APIService
{
    public:
        APIService();
        void setCredentials();
        String getState();
        void setHeader();        
        void connectToAPI();
        void writeFile(fs::FS &fs, const char * path, const char * message);
        String readFile(fs::FS &fs, const char * path);
        void startSPIFFS();
    private:
        String _urlOfBuild;
        String _authorizationToken;
};

#endif
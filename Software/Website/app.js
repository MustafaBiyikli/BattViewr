const express = require("express");
const app = express();

const path = require("path");
const router = express.Router();

router.get("/", function(req, res) {
    res.sendFile(path.join(__dirname + "/html/index.html"));
});

router.get("/home", function(req, res) {
    res.sendFile(path.join(__dirname + "/html/index.html"));
});

app.use(express.static(__dirname));

//add the router
app.use("/", router);

const port = 8000;
app.listen(port, () => {
    console.log(`App running on: ${port}`);
});

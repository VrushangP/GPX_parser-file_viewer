'use strict'

let dbConf = {
    host: '',
    user: '',
    password: '',
    database: ''
};

async function print_tables() {
    const mysql = require('mysql2/promise');

    let connection;

    try {
        connection = await mysql.createConnection(dbConf);
        const [rows1, fields1] = await connection.execute('SELECT distinct * from `FILE` ORDER BY `file_name`');
        // console.log("\nSorted FILE:");
        for (let row of rows1) {
            // console.log("ID:\t" + row.gpx_id + " FileName:\t" + row.file_name + " Version:\t" + row.ver + " Creator:\t" + row.creator);
        }

        const [rows2, fields2] = await connection.execute('SELECT * from `ROUTE` ORDER BY `gpx_id`');
        // console.log("\nSorted ROUTE:");
        for (let row of rows2) {
            // console.log("ID:\t" + row.route_id + " RouteName:\t" + row.route_name + " Length:\t" + row.route_len + " gpxID:\t" + row.gpx_id);
        }

        const [rows3, fields3] = await connection.execute('SELECT distinct * from `POINT` ORDER BY `route_id`');
        // console.log("\nSorted POINT:");
        for (let row of rows3) {
            // console.log("ID:\t" + row.point_id + " PointIndex:\t" + row.point_index + " Latitude:\t" + row.latitude + " Longitude:\t" + row.longitude + ' routeID:\t' + row.route_id + ' Point Name:' + row.point_name);
        }
    } catch (e) {
        console.log("Query error: " + e);
    } finally {
        if (connection && connection.end) connection.end();
    }
}

async function print_route_names() {
    const mysql = require('mysql2/promise');
    let connection;

    try {
        connection = await mysql.createConnection(dbConf);
        let retStr = [];
        let i = 0;

        const [rows2, fields2] = await connection.execute('SELECT * from `ROUTE` ORDER BY `route_name`');
        // console.log("\nSorted ROUTE:");
        for (let row of rows2) {
            retStr[i++] = row.route_name;
            // console.log("ID:\t" + row.route_id + " RouteName:\t" + row.route_name + " Length:\t" + row.route_len + " gpxID:\t" + row.gpx_id);
        }

        return retStr;
    } catch (e) {
        console.log("Query error: " + e);
    } finally {
        if (connection && connection.end) connection.end();
    }
}

async function similar_name(file_name) {
    const mysql = require('mysql2/promise');
    let connection;

    try {
        connection = await mysql.createConnection(dbConf);
        var id = 0;

        const [rows1, fields1] = await connection.execute('SELECT distinct * from `FILE` ORDER BY `file_name`');
        // console.log("\nSorted FILE:");
        for (let row of rows1) {
            if (file_name == row.file_name) {
                return false;
            }
        }
        return true;
    } catch (e) {
        console.log("Query error: " + e);
    } finally {
        if (connection && connection.end) connection.end();
    }
}

async function return_gpxid(file_name) {
    const mysql = require('mysql2/promise');
    let connection;

    try {
        connection = await mysql.createConnection(dbConf);
        var id = 0;

        const [rows1, fields1] = await connection.execute('SELECT distinct * from `FILE` ORDER BY `file_name`');
        // console.log("\nSorted FILE:");
        for (let row of rows1) {
            if (file_name == row.file_name) {
                // console.log("ID:\t" + row.gpx_id + " FileName:\t" + row.file_name + " Version:\t" + row.ver + " Creator:\t" + row.creator);
                id = row.gpx_id;
            }
        }
        if (id != 0) {
            return id;
        }
    } catch (e) {
        console.log("Query error: " + e);
    } finally {
        if (connection && connection.end) connection.end();
    }
}

async function add_to_rename_route(oldname, newname) {
    const mysql = require('mysql2/promise');
    let connection;

    try {
        connection = await mysql.createConnection(dbConf);
        let retStr = [];
        let i = 0;
        var sql = "UPDATE ROUTE SET route_name = '" + newname + "' WHERE route_name = '" + oldname + "'";
        // console.log(sql);
        connection.query(sql);

        return retStr;
    } catch (e) {
        console.log("Query error: " + e);
    } finally {
        if (connection && connection.end) connection.end();
    }
}

async function print_table_route(order) {
    const mysql = require('mysql2/promise');
    let connection;

    try {
        connection = await mysql.createConnection(dbConf);
        let retStr = [];
        let i = 0;

        const [rows2, fields2] = await connection.execute('SELECT * from `ROUTE` ORDER BY `' + order +'`');
        // console.log("\nSorted ROUTE:");
        for (let row of rows2) {
            retStr[i++] = row.route_id + "," + row.route_name+ "," + row.route_len + "," + row.gpx_id;
            // console.log("ID:\t" + row.route_id + " RouteName:\t" + row.route_name + " Length:\t" + row.route_len + " gpxID:\t" + row.gpx_id);
        }

        return retStr;
    } catch (e) {
        console.log("Query error: " + e);
    } finally {
        if (connection && connection.end) connection.end();
    }
}

async function print_table_route_points(file) {
    const mysql = require('mysql2/promise');
    let connection;

    try {
        connection = await mysql.createConnection(dbConf);
        let retStr = [];
        let i = 0;
        var routeid;

        const [rows1, fields1] = await connection.execute('SELECT distinct * from `ROUTE` ORDER BY `route_name`');
        // console.log("\nSorted FILE:");
        for (let row of rows1) {
            if (file == row.route_name) {
                routeid = row.route_id;
            }
        }

        if (routeid != '') {
            const [rows3, fields3] = await connection.execute('SELECT distinct * from `POINT` ORDER BY `point_index`');
            // console.log("\nSorted POINT:");
            for (let row of rows3) {
                if (row.route_id == routeid) {
                    retStr[i++] = row.point_id + "," + row.point_index+ "," + row.latitude + "," + row.longitude+ "," + row.point_name + "," + row.route_id;
                    // console.log("ID:\t" + row.point_id + " PointIndex:\t" + row.point_index + " Latitude:\t" + row.latitude + " Longitude:\t" + row.longitude + ' routeID:\t' + row.route_id);
                }
            }
        }

        return retStr;
    } catch (e) {
        console.log("Query error: " + e);
    } finally {
        if (connection && connection.end) connection.end();
    }
}

async function print_table_file_point(file, order) {
    const mysql = require('mysql2/promise');
    let connection;

    try {
        connection = await mysql.createConnection(dbConf);
        let retStr = [];
        let routeid = []
        let i = 0;
        let k = 0;
        var gpxid;

        const [rows1, fields1] = await connection.execute('SELECT distinct * from `FILE` ORDER BY `file_name`');
        // console.log("\nSorted FILE:");
        for (let row of rows1) {
            if (file == row.file_name) {
                gpxid = row.gpx_id;
                // console.log(file + "---" + row.gpx_id);
            }
            // console.log("ID:\t" + row.gpx_id + " FileName:\t" + row.file_name + " Version:\t" + row.ver + " Creator:\t" + row.creator);
        }

        const [rows2, fields2] = await connection.execute('SELECT distinct * from `ROUTE` ORDER BY `' + order + '`');
        // console.log("\nSorted FILE:");
        for (let row of rows2) {
            if (gpxid == row.gpx_id) {
                routeid[i++] = row.route_id;
            }
        }

        if (gpxid != '') {
            for (let j = 0; j < routeid.length; j++) {
                const [rows3, fields3] = await connection.execute('SELECT distinct * from `POINT` ORDER BY `point_index`');
                // console.log("\nSorted POINT:");
                for (let row of rows3) {
                    if (row.route_id == routeid[j]) {
                        retStr[k++] = row.point_id + "," + row.point_index+ "," + row.latitude + "," + row.longitude+ "," + row.point_name + "," + row.route_id;
                        // console.log("ID:\t" + row.point_id + " PointIndex:\t" + row.point_index + " Latitude:\t" + row.latitude + " Longitude:\t" + row.longitude + ' routeID:\t' + row.route_id);
                    }
                }
            }            
        }

        return retStr;
    } catch (e) {
        console.log("Query error: " + e);
    } finally {
        if (connection && connection.end) connection.end();
    }
}

async function print_table_n_route(file, order, order2) {
    const mysql = require('mysql2/promise');
    let connection;

    try {
        connection = await mysql.createConnection(dbConf);
        let idStr = [];
        let retStr = [];
        let lenStr = [];
        let gpxidStr = [];
        let retStr2 = []
        let i = 0;
        let j = 0;
        var gpxid;

        const [rows1, fields1] = await connection.execute('SELECT distinct * from `FILE` ORDER BY `file_name`');
        // console.log("\nSorted FILE:");
        for (let row of rows1) {
            if (file == row.file_name) {
                gpxid = row.gpx_id;
                // console.log(file + "---" + row.gpx_id);
            }
            // console.log("ID:\t" + row.gpx_id + " FileName:\t" + row.file_name + " Version:\t" + row.ver + " Creator:\t" + row.creator);
        }

        if (gpxid != '') {
            if (order == 'ASEN') {
                const [rows2, fields2] = await connection.execute('SELECT * from `ROUTE` ORDER BY `route_len`');
                // console.log("\nSorted ROUTE:");
                for (let row of rows2) {
                    retStr[j++] = row.route_id + "," + row.route_name+ "," + row.route_len + "," + row.gpx_id;
                    if (row.gpx_id == gpxid) {
                        // retStr[i++] = row.route_id + "," + row.route_name+ "," + row.route_len + "," + row.gpx_id;
                        // retStr[i++] = [[row.route_id], [row.route_name], [row.route_len], [row.gpx_id]];

                        retStr2[i] = row.route_id + "," + row.route_name+ "," + row.route_len + "," + row.gpx_id;
                        idStr[i++] = row.route_id;

                        // console.log("ID:\t" + row.route_id + " RouteName:\t" + row.route_name + " Length:\t" + row.route_len + " gpxID:\t" + row.gpx_id);
                    }
                }
            } else if (order == 'DESN') {
                const [rows2, fields2] = await connection.execute('SELECT * from `ROUTE` ORDER BY `route_len` DESC');
                // console.log("\nSorted ROUTE:");
                for (let row of rows2) {
                    retStr[j++] = row.route_id + "," + row.route_name+ "," + row.route_len + "," + row.gpx_id;
                    if (row.gpx_id == gpxid) {
                        // retStr[i++] = [[row.route_id], [row.route_name], [row.route_len], [row.gpx_id]];
                        retStr2[i] = row.route_id + "," + row.route_name+ "," + row.route_len + "," + row.gpx_id;
                        idStr[i++] = row.route_id;
                        // console.log("ID:\t" + row.route_id + " RouteName:\t" + row.route_name + " Length:\t" + row.route_len + " gpxID:\t" + row.gpx_id);
                    }
                }
            }
            i = 0;
            if (order2 == 'Name' && order == 'DESN') {
                const [rows3, fields2] = await connection.execute('SELECT * from `ROUTE` ORDER BY `route_name` DESC');
                for (let row of rows3) {
                    for (let index = 0; index < retStr.length; index++) {
                        if (row.route_id == idStr[index]) {
                            retStr2[i++] = row.route_id + "," + row.route_name+ "," + row.route_len + "," + row.gpx_id;
                            // retStr[i++] = [[row.route_id], [row.route_name], [row.route_len], [row.gpx_id]];
                            // console.log("ID:\t" + row.route_id + " RouteName:\t" + row.route_name + " Length:\t" + row.route_len + " gpxID:\t" + row.gpx_id);
                        }
                    }
                }
            } else if (order2 == 'Name' && order == 'ASEN') {
                const [rows3, fields2] = await connection.execute('SELECT * from `ROUTE` ORDER BY `route_name`');
                for (let row of rows3) {
                    for (let index = 0; index < retStr.length; index++) {
                        if (row.route_id == idStr[index]) {
                            retStr2[i++] = row.route_id + "," + row.route_name+ "," + row.route_len + "," + row.gpx_id;
                            // retStr[i++] = [[row.route_id], [row.route_name], [row.route_len], [row.gpx_id]];
                            // console.log("ID:\t" + row.route_id + " RouteName:\t" + row.route_name + " Length:\t" + row.route_len + " gpxID:\t" + row.gpx_id);
                        }
                    }
                }
            }
        }
        // console.log(retStr);
        // console.log(retStr2);
        // console.log(idStr);
        return retStr2;
    } catch (e) {
        console.log("Query error: " + e);
    } finally {
        if (connection && connection.end) connection.end();
    }
}


async function print_table_file_route(file, order) {
    const mysql = require('mysql2/promise');
    let connection;

    try {
        connection = await mysql.createConnection(dbConf);
        let retStr = [];
        let i = 0;
        var gpxid;

        const [rows1, fields1] = await connection.execute('SELECT distinct * from `FILE` ORDER BY `file_name`');
        // console.log("\nSorted FILE:");
        for (let row of rows1) {
            if (file == row.file_name) {
                gpxid = row.gpx_id;
                // console.log(file + "---" + row.gpx_id);
            }
            // console.log("ID:\t" + row.gpx_id + " FileName:\t" + row.file_name + " Version:\t" + row.ver + " Creator:\t" + row.creator);
        }

        if (gpxid != '') {
            const [rows2, fields2] = await connection.execute('SELECT * from `ROUTE` ORDER BY `' + order +'`');
            // console.log("\nSorted ROUTE:");
            for (let row of rows2) {
                if (row.gpx_id == gpxid) {
                    retStr[i++] = row.route_id + "," + row.route_name+ "," + row.route_len + "," + row.gpx_id;
                    // console.log("ID:\t" + row.route_id + " RouteName:\t" + row.route_name + " Length:\t" + row.route_len + " gpxID:\t" + row.gpx_id);
                }
            }
        }

        return retStr;
    } catch (e) {
        console.log("Query error: " + e);
    } finally {
        if (connection && connection.end) connection.end();
    }
}

async function displayy() {
    const mysql = require('mysql2/promise');
    let connection;

    try {
        connection = await mysql.createConnection(dbConf);
        const [rows1, fields1] = await connection.execute('SELECT distinct * from `FILE` ORDER BY `file_name`');
        const [rows2, fields2] = await connection.execute('SELECT * from `ROUTE` ORDER BY `gpx_id`');
        const [rows3, fields3] = await connection.execute('SELECT distinct * from `POINT` ORDER BY `route_id`');

        // console.log("s1: " + rows1.length + " s2: " + rows2.length + " s3: " + rows3.length);
        var ret = [rows1.length, rows2.length, rows3.length];
        return ret;
    } catch (e) {
        console.log("Query error: " + e);
    } finally {
        if (connection && connection.end) connection.end();
    }
}

async function clear() {
    const mysql = require('mysql2/promise');
    let connection;

    try {
        connection = await mysql.createConnection(dbConf);
        // connection.execute("create table if not exists STU (route_id int not null primary key auto_increment,  route_name VARCHAR(256), route_len FLOAT(15,7) NOT NULL)");

        var sq1 = "DELETE FROM POINT";
        connection.query(sq1);
        var sq2 = "DELETE FROM ROUTE";
        connection.query(sq2);
        var sq3 = "DELETE FROM FILE";
        connection.query(sq3);

    } catch (e) {
        console.log("Query error: " + e);
    } finally {
        if (connection && connection.end) connection.end();
    }
}

async function setup(host, user, password, database) {
    // get the client
    const mysql = require('mysql2/promise');

    let connection;
    dbConf.host = host;
    dbConf.user = user;
    dbConf.password = password;
    dbConf.database = database;
    // console.log(dbConf.password);

    try {
        connection = await mysql.createConnection(dbConf);

        connection.execute("create table if not exists FILE (gpx_id int not null primary key auto_increment, file_name VARCHAR(60) NOT NULL UNIQUE, ver DECIMAL(2,1) NOT NULL, creator VARCHAR(256) NOT NULL)");
        connection.execute("create table if not exists ROUTE (route_id int not null primary key auto_increment, route_name VARCHAR(256), route_len FLOAT(15,7) NOT NULL, gpx_id INT NOT NULL, FOREIGN KEY(gpx_id) REFERENCES FILE(gpx_id) ON DELETE CASCADE)");
        connection.execute("create table if not exists POINT (point_id int not null auto_increment primary key, point_index INT NOT NULL, latitude DECIMAL(11,7) NOT NULL, longitude DECIMAL(11,7) NOT NULL, point_name VARCHAR(256), route_id INT NOT NULL, FOREIGN KEY(route_id) REFERENCES ROUTE(route_id) ON DELETE CASCADE)");

        // var sq3 = "DROP TABLE POINT";
        // connection.query(sq3);
        // var sq2 = "DROP TABLE ROUTE";
        // connection.query(sq2);
        // var sq1 = "DROP TABLE FILE";
        // connection.query(sq1);

        connection.end();
        return 1;
    } catch (e) {
        console.log("Query error: 2" + e);
    } finally {
        if (connection && connection.end) connection.end();
    }
}

async function add_to_table(FILE_data) {
    // get the client
    const mysql = require('mysql2/promise');
    let connection;

    try {
        connection = await mysql.createConnection(dbConf);

        connection.execute("create table if not exists FILE (gpx_id int not null primary key auto_increment, file_name VARCHAR(60) NOT NULL UNIQUE, ver DECIMAL(2,1) NOT NULL, creator VARCHAR(256) NOT NULL)");
        connection.execute("create table if not exists ROUTE (route_id int not null primary key auto_increment, route_name VARCHAR(256), route_len FLOAT(15,7) NOT NULL, gpx_id INT NOT NULL, FOREIGN KEY(gpx_id) REFERENCES FILE(gpx_id) ON DELETE CASCADE)");
        connection.execute("create table if not exists POINT (point_id int not null auto_increment primary key, point_index INT NOT NULL, latitude DECIMAL(11,7) NOT NULL, longitude DECIMAL(11,7) NOT NULL, point_name VARCHAR(256), route_id INT NOT NULL, FOREIGN KEY(route_id) REFERENCES ROUTE(route_id) ON DELETE CASCADE)");

        const resp = await connection.query(FILE_data);

        // connection.end();
        return resp[0].insertId;

    } catch (e) {
        console.log("Query error: 1 " + e);
    } finally {
        if (connection && connection.end) connection.end();
    }
}





async function add_all_points( file ) {
    // get the client
    const mysql = require('mysql2/promise');
    let connection;

    try {
        connection = await mysql.createConnection(dbConf);
        let retStr = [];
        var index = 0;
        for (let j = 0; j < file.length; j++) {

            let gpxDoc = shared.createValidGPXdoc("./uploads/" + file[j], "./parser/bin/gpx.xsd");
            let valid = shared.validateGPXDoc(gpxDoc, "parser/bin/gpx.xsd");
            if (valid == true) {
                var tpr = shared.GPXtoJSON(gpxDoc);
            
    
            var tp2 = tpr.replace(/['"]+/g, '');
            retStr[index] = tp2.replace('{version:', ",");
            retStr[index] = retStr[index].replace(',creator:', ",");
            retStr[index] = retStr[index].replace(',numWaypoints:', ",");
            retStr[index] = retStr[index].replace(',numRoutes:', ",");
            retStr[index] = retStr[index].replace(',numTracks:', ",");
            retStr[index] = retStr[index].replace('}', ",");
            retStr[index] = file[j] + retStr[index];
            var row_spliterr = retStr[index].split(',');
            let file_inp = "REPLACE INTO FILE (file_name, ver, creator) VALUES ('";
            file_inp = file_inp.concat(row_spliterr[0]);
            file_inp = file_inp.concat("','");
            file_inp = file_inp.concat(row_spliterr[1]);
            file_inp = file_inp.concat("','");
            file_inp = file_inp.concat(row_spliterr[2]);
            file_inp = file_inp.concat("')");
            index++;
            // console.log(file_inp);
            // const file_ID = add_to_table(file_inp);
            
            const resp = await connection.query(file_inp);
            const result = resp[0].insertId;
            // console.log(ret);
    
            // file_ID.then(function (result) {
                // console.log(result) // "Some User token"
                var tpr3 = shared.GPXViewtoJSON_point(gpxDoc);
                var json_spliterr = tpr3.split('],[');
                if (json_spliterr[2] != '') {
                    var route_spliterr = json_spliterr[2].split('},{');
                    // console.log(route_spliterr);
                    // console.log(json_spliterr[2]);
    
                    for (var index2 = 0; index2 < route_spliterr.length; index2++) {
                        route_spliterr[index2] = route_spliterr[index2].replace(']', "");
                        route_spliterr[index2] = route_spliterr[index2].replace('[', "");
                        route_spliterr[index2] = route_spliterr[index2].replace('}', "");
                        route_spliterr[index2] = route_spliterr[index2].replace('{', "");
                        route_spliterr[index2] = route_spliterr[index2].replace('"name":"', ",");
                        route_spliterr[index2] = route_spliterr[index2].replace('","numPoints":', ",");
                        route_spliterr[index2] = route_spliterr[index2].replace(',"len":', ",");
                        route_spliterr[index2] = route_spliterr[index2].replace(',"loop":', ",");
                        var num = index2 + 1;
                        route_spliterr[index2] = 'Route ' + num + route_spliterr[index2];
                        var row_spliterr2 = route_spliterr[index2].split(',');
                        let route_inp = "INSERT IGNORE INTO ROUTE (route_name, route_len, gpx_id) VALUES (";
                        if (row_spliterr2[3] != "") {
                            if (row_spliterr2[1] == 'None' || row_spliterr2[1] == '') {
                                route_inp = route_inp.concat('NULL');
                            } else {
                                route_inp = route_inp.concat("'" + row_spliterr2[1] + "'");
                            }
                            // route_inp = route_inp.concat(row_spliterr2[1]);
                            route_inp = route_inp.concat(",");
                            route_inp = route_inp.concat(row_spliterr2[3]);
                            route_inp = route_inp.concat(",");
                            route_inp = route_inp.concat(result);
                            route_inp = route_inp.concat(")");
                            // console.log(route_spliterr[index2] + route_spliterr.length);
                            if (row_spliterr2[1] != undefined && row_spliterr2[3] != undefined) {
    
                                var point_spliterr = route_spliterr[index2].split('>,<');
                                // console.log(route_inp);
    
                                // const ret = add_to_table(route_inp);
                                // console.log(route_inp);
                                const resp1 = await connection.query(route_inp);
                                const res = resp1[0].insertId;
                                // ret.then(function (res) {
                                    // console.log(res); // "Some User token"
    
                                    for (var index3 = 0; index3 < point_spliterr.length; index3++) {
    
                                        point_spliterr[index3] = point_spliterr[index3].split("<").pop();
                                        point_spliterr[index3] = point_spliterr[index3].replace('>', "");
                                        point_spliterr[index3] = point_spliterr[index3].replace(']', "");
                                        // console.log("\t" + point_spliterr[index3]);
    
                                        point_spliterr[index3] = point_spliterr[index3].replace('"index":"', "");
                                        point_spliterr[index3] = point_spliterr[index3].replace('","longitude":', ",");
                                        point_spliterr[index3] = point_spliterr[index3].replace(',"latitude":', ",");
                                        point_spliterr[index3] = point_spliterr[index3].replace(',"name":', ",");
    
                                        var point_spliterr2 = point_spliterr[index3].split(',');
                                        let point_inp = "INSERT IGNORE INTO POINT (point_index, latitude, longitude, point_name, route_id) VALUES ('";
    
                                        point_inp = point_inp.concat(point_spliterr2[0]);
                                        point_inp = point_inp.concat("','");
                                        point_inp = point_inp.concat(point_spliterr2[2]);
                                        point_inp = point_inp.concat("','");
                                        point_inp = point_inp.concat(point_spliterr2[1]);
                                        point_inp = point_inp.concat("',");
                                        if (point_spliterr2[3] == 'None') {
                                            point_inp = point_inp.concat('NULL');
                                        } else {
                                            point_inp = point_inp.concat("'" + point_spliterr2[3] + "'");
                                        }
                                        // point_inp = point_inp.concat(point_spliterr2[3]);   
                                        point_inp = point_inp.concat(",'");
                                        point_inp = point_inp.concat(res);
                                        point_inp = point_inp.concat("')");
    
                                        // const point_ID = add_to_table(point_inp);
                                        // console.log(point_inp);
                                        const resp2 = await connection.query(point_inp);
                                        const rest = resp2[0].insertId;
                                        // point_ID.then(function (res) {
    
                                        // });
                                    }
                                // })
                            }
                        }
                    }
                }
            }
            shared.deleteGPXdoc(gpxDoc);
        }

        // })

    } catch (e) {
        console.log("Query error: 3 " + e);
    } finally {
        if (connection && connection.end) connection.end();
    }
}
// C library API
const ffi = require('ffi-napi');

// Express App (Routes)
const express = require("express");
const app = express();
const path = require("path");
const fileUpload = require('express-fileupload');

let shared = ffi.Library('./parser/bin/libgpxparser.so', {
    'round10': ['float', ['float']],
    'createValidGPXdoc': ['pointer', ['string', 'string']],
    'GPXtoJSON': ['string', ['pointer']],
    'validateGPXDoc': ['bool', ['pointer', 'string']],
    'routeToJSON': ['string', ['pointer']],
    'GPXViewtoJSON': ['string', ['pointer']],
    'OtherDatatoJSON': ['string', ['pointer', 'string']],
    'GPXViewtoJSON_point': ['string', ['pointer']],
    'JSONtoWaypoint': ['pointer', ['string', 'string']],
    'JSONtoRoute': ['pointer', ['string']],
    'addWaypoint': ['void', ['pointer', 'pointer']],
    'addRoute': ['void', ['pointer', 'pointer']],
    'writeGPXdoc': ['bool', ['pointer', 'string']],
    'getRouteLen': ['float', ['pointer']],
    'GPXRouteRename': ['bool', ['pointer', 'string', 'string']],
    'JSONtoGPX': ['pointer', ['string']],
    'deleteGPXdoc': ['void', ['pointer']]

});

app.use(fileUpload());
app.use(express.static(path.join(__dirname + '/uploads')));

// Minimization
const fs = require('fs');
const JavaScriptObfuscator = require('javascript-obfuscator');

// Important, pass in port as in `npm run dev 1234`, do not change
const portNum = process.argv[2];

// Send HTML at root, do not change
app.get('/', function (req, res) {
    res.sendFile(path.join(__dirname + '/public/index.html'));
});

// Send Style, do not change
app.get('/style.css', function (req, res) {
    //Feel free to change the contents of style.css to prettify your Web app
    res.sendFile(path.join(__dirname + '/public/style.css'));
});

// Send obfuscated JS, do not change
app.get('/index.js', function (req, res) {
    fs.readFile(path.join(__dirname + '/public/index.js'), 'utf8', function (err, contents) {
        const minimizedContents = JavaScriptObfuscator.obfuscate(contents, { compact: true, controlFlowFlattening: true });
        res.contentType('application/javascript');
        res.send(minimizedContents._obfuscatedCode);
    });
});

//Respond to POST requests that upload files to uploads/ directory
app.post('/upload', function (req, res) {
    if (!req.files) {
        return res.status(400).send('No files were uploaded.');
    }

    let uploadFile = req.files.uploadFile;

    // Use the mv() method to place the file somewhere on your server
    uploadFile.mv('uploads/' + uploadFile.name, function (err) {
        if (err) {
            return res.status(500).send(err);
        }

        res.redirect('/');
    });
});

//Respond to GET requests for files in the uploads/ directory
app.get('/uploads/:name', function (req, res) {
    fs.stat('uploads/' + req.params.name, function (err, stat) {
        if (err == null) {
            res.sendFile(path.join(__dirname + '/uploads/' + req.params.name));
        } else {
            // console.log('Error in file downloading route: ' + err);
            res.send('');
        }
    });
});

//******************** Your code goes here ********************

//Sample endpoint
app.get('/endpoint1', function (req, res) {
    let retStr = req.query.data1 + " " + req.query.data2;
    res.send(
        {
            somethingElse: retStr
        }
    );
});

app.get('/GPX_newfile', function (req, res) {
    let file_n = req.query.file_name;
    let ver = req.query.ver;
    let creator = req.query.creator;
    let retStr;

    const gpxid = similar_name(file_n);
    gpxid.then(function(result) {
        if (result == true) {
            let str = '{"version":' + ver + ',"creator":"' + creator + '"}'
            let gpxDoc = shared.JSONtoGPX(str);
            let valid = shared.validateGPXDoc(gpxDoc, "parser/bin/gpx.xsd");
            // console.log("-" + file_n + "-");
            if (valid == true) {
                // console.log("valid file inputted");
                let succ = shared.writeGPXdoc(gpxDoc, "./uploads/" + file_n);
                if (succ == true) {
                    // console.log("file uploaded");
                    retStr = "file uploaded";
                } else {
                    // console.log("file failed to upload");
                }
            } else {
                retStr = "file of failed to validate against schema"
                // console.log("file of failed to validate against schema");
            }
        } else {
            retStr = "file of similar name already exists on DB";
            // console.log("file of similar name already exists on DB");
        }
        res.send({
            somethingElse: retStr
        });

    });
});

app.get('/retrieve_routes', function (req, res) {
    let retStr = req.query.data1 + " " + req.query.data2;
    const file_ID = print_route_names();
    // console.log(ret);

    file_ID.then(function(result) {
        // console.log(result) // "Some User token"
        res.send({
            somethingElse: result
        });
    });
});

app.get('/disp_db', function (req, res) {
    let retStr = [];
    const file_ID = displayy();

    file_ID.then(function(result) {
        // console.log(result);
        retStr = result;
        print_tables();
        res.send({
            somethingElse: retStr
        });
    });
});

app.get('/clear_db', function (req, res) {
    let retStr = [];
    const file_ID = clear();

    file_ID.then(function(result) {
        // console.log("new table vv");
        retStr = result;
        // print_tables();
        res.send({
            somethingElse: retStr
        });
    });
});

app.get('/store_db', function (req, res) {
    // console.log("this is happening");
    let file_name = [];
    let i = 0;
    fs.readdir(path.join(__dirname + '/uploads'), 'utf8', function (err, contents) {
        contents.forEach(file => {
            file_name[i++] = file;
        });
    });

    add_all_points(file_name);

});

// app.get('/store_db', function (req, res) {
//     // console.log("this is happening");
//     fs.readdir(path.join(__dirname + '/uploads'), 'utf8', function (err, contents) {
//         let retStr = [];
//         var index = 0;
//         contents.forEach(file => {
//             var file_name = file;
//             let gpxDoc = shared.createValidGPXdoc("./uploads/" + file_name, "./parser/bin/gpx.xsd");
//             let valid = shared.validateGPXDoc(gpxDoc, "parser/bin/gpx.xsd");
//             if (valid == true) {
//                 var tpr = shared.GPXtoJSON(gpxDoc);
//                 var tp2 = tpr.replace(/['"]+/g, '');
//                 retStr[index] = tp2.replace('{version:', ",");
//                 retStr[index] = retStr[index].replace(',creator:', ",");
//                 retStr[index] = retStr[index].replace(',numWaypoints:', ",");
//                 retStr[index] = retStr[index].replace(',numRoutes:', ",");
//                 retStr[index] = retStr[index].replace(',numTracks:', ",");
//                 retStr[index] = retStr[index].replace('}', ",");
//                 retStr[index] = file + retStr[index];
//                 var row_spliterr = retStr[index].split(',');
//                 let file_inp = "REPLACE INTO FILE (file_name, ver, creator) VALUES ('";
//                 file_inp = file_inp.concat(row_spliterr[0]);
//                 file_inp = file_inp.concat("','");
//                 file_inp = file_inp.concat(row_spliterr[1]);    
//                 file_inp = file_inp.concat("','");
//                 file_inp = file_inp.concat(row_spliterr[2]);
//                 file_inp = file_inp.concat("')");
//                 index++;
//                 // console.log(file_inp);
//                 const file_ID = add_to_table(file_inp);
//                 // console.log(ret);

//                 file_ID.then(function(result) {
//                     // console.log(result) // "Some User token"
//                     var tpr3 = shared.GPXViewtoJSON_point(gpxDoc);
//                     var json_spliterr = tpr3.split('],[');
//                     if (json_spliterr[2] != '') {
//                         var route_spliterr = json_spliterr[2].split('},{');
//                         // console.log(route_spliterr);
//                         // console.log(json_spliterr[2]);

//                         for (var index2 = 0; index2 < route_spliterr.length; index2++) {
//                             route_spliterr[index2] = route_spliterr[index2].replace(']', "");
//                             route_spliterr[index2] = route_spliterr[index2].replace('[', "");
//                             route_spliterr[index2] = route_spliterr[index2].replace('}', "");
//                             route_spliterr[index2] = route_spliterr[index2].replace('{', "");
//                             route_spliterr[index2] = route_spliterr[index2].replace('"name":"', ",");
//                             route_spliterr[index2] = route_spliterr[index2].replace('","numPoints":', ",");
//                             route_spliterr[index2] = route_spliterr[index2].replace(',"len":', ",");
//                             route_spliterr[index2] = route_spliterr[index2].replace(',"loop":', ",");
//                             var num = index2 + 1;
//                             route_spliterr[index2] = 'Route ' + num + route_spliterr[index2];
//                             var row_spliterr2 = route_spliterr[index2].split(',');
//                             let route_inp = "INSERT IGNORE INTO ROUTE (route_name, route_len, gpx_id) VALUES (";
//                             if (row_spliterr2[3] != "") {
//                                 if (row_spliterr2[1] == 'None') {
//                                     route_inp = route_inp.concat('NULL');
//                                 } else {
//                                     route_inp = route_inp.concat("'" + row_spliterr2[1] + "'");
//                                 } 
//                                 // route_inp = route_inp.concat(row_spliterr2[1]);
//                                 route_inp = route_inp.concat(",'");
//                                 route_inp = route_inp.concat(row_spliterr2[3]);   
//                                 route_inp = route_inp.concat("','");
//                                 route_inp = route_inp.concat(result); 
//                                 route_inp = route_inp.concat("')");
//                                 // console.log(route_spliterr[index2] + route_spliterr.length);
//                                 if (row_spliterr2[1] != undefined && row_spliterr2[3] != undefined) {
                                    
//                                     var point_spliterr = route_spliterr[index2].split('>,<');
//                                     // console.log(route_inp);

//                                     const ret = add_to_table(route_inp);
//                                     ret.then(function(res) {
//                                         // console.log(res); // "Some User token"

//                                         for (var index3 = 0; index3 < point_spliterr.length; index3++) {

//                                             point_spliterr[index3] = point_spliterr[index3].split("<").pop();
//                                             point_spliterr[index3] = point_spliterr[index3].replace('>', "");
//                                             point_spliterr[index3] = point_spliterr[index3].replace(']', "");
//                                             // console.log("\t" + point_spliterr[index3]);

//                                             point_spliterr[index3] = point_spliterr[index3].replace('"index":"', "");
//                                             point_spliterr[index3] = point_spliterr[index3].replace('","longitude":', ",");
//                                             point_spliterr[index3] = point_spliterr[index3].replace(',"latitude":', ",");
//                                             point_spliterr[index3] = point_spliterr[index3].replace(',"name":', ",");

//                                             var point_spliterr2 = point_spliterr[index3].split(',');
//                                             let point_inp = "INSERT IGNORE INTO POINT (point_index, latitude, longitude, point_name, route_id) VALUES ('";

//                                             point_inp = point_inp.concat(point_spliterr2[0]);
//                                             point_inp = point_inp.concat("','");
//                                             point_inp = point_inp.concat(point_spliterr2[2]);    
//                                             point_inp = point_inp.concat("','");
//                                             point_inp = point_inp.concat(point_spliterr2[1]);
//                                             point_inp = point_inp.concat("',");
//                                             if (point_spliterr2[3] == 'None') {
//                                                 point_inp = point_inp.concat('NULL');
//                                             } else {
//                                                 point_inp = point_inp.concat("'" + point_spliterr2[3] + "'");
//                                             } 
//                                             // point_inp = point_inp.concat(point_spliterr2[3]);   
//                                             point_inp = point_inp.concat(",'");
//                                             point_inp = point_inp.concat(res); 
//                                             point_inp = point_inp.concat("')");

//                                             const point_ID = add_to_table(point_inp);
//                                             point_ID.then(function(res) {

//                                             });
//                                         }
//                                     })
//                                 }
//                             }
//                         }
//                     }
//                 })
//             }
//         });
//     });
// });

app.get('/login_db', function (req, res) {
    	
	var hostName = req.query.hostName;
	var username = req.query.username;
	var password = req.query.password;
	var dataBase = req.query.dataBase;

    setup(hostName, username, password, dataBase);

    let retStr = req.query.data1 + " " + req.query.data2;
    res.send({
        somethingElse: retStr
    });
});

app.get('/GPX_rename', function (req, res) {
    let file_n = req.query.file_name;
    let route_name = req.query.route_name;
    let new_route_name = req.query.new_route_name;
    let retStr;

    let gpxDoc = shared.createValidGPXdoc("./uploads/" + file_n, "./parser/bin/gpx.xsd");
    let valid = shared.validateGPXDoc(gpxDoc, "parser/bin/gpx.xsd");
    if (valid == true) {
        const gpxid = return_gpxid(file_n);

        gpxid.then(function(result) {
            // console.log(result) // "Some User token"
            let succ = shared.GPXRouteRename(gpxDoc, route_name, new_route_name);
            if (succ == true) {
                let write_succ = shared.writeGPXdoc(gpxDoc, "./uploads/" + file_n);
                if (write_succ == true) {
                    // console.log("file updated");
                    retStr = "file updated";

                    const ret = add_to_rename_route(route_name, new_route_name);
                } else {
                    retStr = "failed to rename route";
                }
            } else {
                retStr = "failed to rename route";
            }
            res.send({
                somethingElse: retStr
            });
        });
    }
});

app.get('/print_route_points', function (req, res) {
    let retStr = req.query.data1 + " " + req.query.data2;
    const file_ID = print_table_route_points(req.query.file);
    // console.log(ret);

    file_ID.then(function(result) {
        // console.log(result) // "Some User token"
        res.send({
            somethingElse: result
        });
    });
});

app.get('/print_N_routes', function (req, res) {
    let retStr = req.query.data1 + " " + req.query.data2;
    const file_ID = print_table_n_route(req.query.file, req.query.order, req.query.order2);
    // console.log(ret);

    file_ID.then(function(result) {
        // console.log(result) // "Some User token"
        res.send({
            somethingElse: result
        });
    });
});

app.get('/print_all_routes', function (req, res) {
    let retStr = req.query.data1 + " " + req.query.data2;
    const file_ID = print_table_route(req.query.data1);
    // console.log(ret);

    file_ID.then(function(result) {
        // console.log(result) // "Some User token"
        res.send({
            somethingElse: result
        });
    });
});

app.get('/print_file_points', function (req, res) {
    let retStr = req.query.data1 + " " + req.query.data2;
    const file_ID = print_table_file_point(req.query.file, req.query.sort);
    // console.log(ret);

    file_ID.then(function(result) {
        // console.log(result) // "Some User token"
        res.send({
            somethingElse: result
        });
    });
});

app.get('/print_file_routes', function (req, res) {
    let retStr = req.query.data1 + " " + req.query.data2;
    const file_ID = print_table_file_route(req.query.file, req.query.sort);
    // console.log(ret);

    file_ID.then(function(result) {
        // console.log(result) // "Some User token"
        res.send({
            somethingElse: result
        });
    });
});

app.get('/GPX_other_data', function (req, res) {
    let file_n = req.query.file_name;
    let retStr = [];
    var index_g = 0;
    let gpxDoc = shared.createValidGPXdoc("./uploads/" + file_n, "./parser/bin/gpx.xsd");
    let valid = shared.validateGPXDoc(gpxDoc, "parser/bin/gpx.xsd");
    if (valid == true) {
        var tpr = shared.OtherDatatoJSON(gpxDoc, req.query.route_name);
        // console.log("is this undef -> " + tpr);
        if (tpr != '') {
            var json_splitterr = tpr.split('},{');
            for (var index = 0; index < json_splitterr.length; index++) {
                json_splitterr[index] = json_splitterr[index].replace('}', "");
                json_splitterr[index] = json_splitterr[index].replace('{', "");
                json_splitterr[index] = json_splitterr[index].replace(']', "");
                json_splitterr[index] = json_splitterr[index].replace('[]', "");
                json_splitterr[index] = json_splitterr[index].replace('"name":"', "");
                json_splitterr[index] = json_splitterr[index].replace('","value":"', ",");
                json_splitterr[index] = json_splitterr[index].replace('"', "");
                // console.log(json_splitterr[index]);
                retStr[index] = json_splitterr[index];
            }
            // console.log('somethin found');
        } else {
            // console.log('no other data found');
        }
    }
    res.send({
        somethingElse: retStr
    });
});

app.get('/append_route', function(req, res) {
    let retStr = 'route successfully appended';
    let file_n = req.query.file;
    let waypointn_count = req.query.n;
    let r_or_t = req.query.r_or_t;
    let name = req.query.name;
    let lat = req.query.lat;
    let lon = req.query.lon;
    let r_name = req.query.r_name;

    // console.log(name, lat, lon);

    let gpxDoc = shared.createValidGPXdoc("./uploads/" + file_n, "./parser/bin/gpx.xsd");
    let valid = shared.validateGPXDoc(gpxDoc, "parser/bin/gpx.xsd");
    if (valid == true) {
        const gpxid = return_gpxid(file_n);

        gpxid.then(function(result) {
            // console.log(result) // "Some User token"
            let route_str = '{"name":"' + r_name + '"}';
            // console.log(route_str);
            let route_ptr = shared.JSONtoRoute(route_str);
            let waypoint_ptr = [];
            for (let index = 0; index < waypointn_count; index++) {
                if (lat[index] >= -90 && lat[index] <= 90 && lon[index] >= -180 && lon[index] <= 180) {
                    let waypoint_str = '{"lat":' + lat[index] + ',"lon":' + lon[index] + '}'
                    // console.log(waypoint_str);
                    waypoint_ptr[index] = shared.JSONtoWaypoint(name[index], waypoint_str);
                    shared.addWaypoint(route_ptr, waypoint_ptr[index]);
                }
            }
            shared.addRoute(gpxDoc, route_ptr);
            let valid2 = shared.validateGPXDoc(gpxDoc, "parser/bin/gpx.xsd");
            if (valid2 == true) {
                let succ = shared.writeGPXdoc(gpxDoc, "./uploads/" + file_n);
                if (succ == 1) {
                    // console.log("file updated");
                    let route_inp = "INSERT IGNORE INTO ROUTE (route_name, route_len, gpx_id) VALUES (";
                    if (r_name == 'None' || r_name == '') {
                        route_inp = route_inp.concat('NULL');
                    } else {
                        route_inp = route_inp.concat("'" + r_name + "'");
                    }
                    route_inp = route_inp.concat(",");
                    var len = shared.getRouteLen(route_ptr);
                    route_inp = route_inp.concat(len);    
                    route_inp = route_inp.concat(",");
                    route_inp = route_inp.concat(result);
                    route_inp = route_inp.concat(")");
                    // console.log(route_inp);
                    const ret = add_to_table(route_inp);
                    ret.then(function(res) {
                        // console.log(res); // "Some User token"
                        for (let index = 0; index < waypointn_count; index++) {
                            let point_inp = "INSERT IGNORE INTO POINT (point_index, latitude, longitude, point_name, route_id) VALUES (";
                            point_inp = point_inp.concat(index);
                            point_inp = point_inp.concat(",");
                            point_inp = point_inp.concat(lat[index]);    
                            point_inp = point_inp.concat(",");
                            point_inp = point_inp.concat(lon[index]);
                            point_inp = point_inp.concat(",");
                            if (name[index] == 'None') {
                                point_inp = point_inp.concat('NULL');
                            } else {
                                point_inp = point_inp.concat("'" + name[index] + "'");
                            }  
                            point_inp = point_inp.concat(",");
                            point_inp = point_inp.concat(res); 
                            point_inp = point_inp.concat(")");
                            // console.log(point_inp);
                            if (lat[index] >= -90 && lat[index] <= 90 && lon[index] >= -180 && lon[index] <= 180) {
                                add_to_table(point_inp);
                            } else {
                                retStr = 'some waypoints may have failed to load\n';
                            }
                        }
                    });
    
                } else {
                    // console.log("failed to write doc");
                    retStr = retStr + "failed to write doc";
                }
            } else {
                // console.log("failed to write doc");

                retStr = 'failed to add route';
            }
            res.send({
                somethingElse: retStr
            });
        });
    }
})

app.get('/GPX_view_table', function (req, res) {
    let file_n = req.query.file_name;
    let retStr = [];
    var index_g = 0;
    // console.log(req.query.data1);
    let gpxDoc = shared.createValidGPXdoc("./uploads/" + file_n, "./parser/bin/gpx.xsd");
    let valid = shared.validateGPXDoc(gpxDoc, "parser/bin/gpx.xsd");
    if (valid == true) {
        var tpr = shared.GPXViewtoJSON(gpxDoc);
        // console.log(" ");
        // console.log(tpr);
        // console.log(" ");
        var json_spliterr = tpr.split('],[');
        if (json_spliterr[1] != '') {
            var track_splitterr = json_spliterr[1].split('},{');
            for (var index = 0; index < track_splitterr.length; index++) {
                track_splitterr[index] = track_splitterr[index].replace('}', "");
                track_splitterr[index] = track_splitterr[index].replace('{', "");
                track_splitterr[index] = track_splitterr[index].replace(']', "");
                track_splitterr[index] = track_splitterr[index].replace('[]', "");
                track_splitterr[index] = track_splitterr[index].replace('"name":"', ",");
                track_splitterr[index] = track_splitterr[index].replace('","numPoints":', ",");
                track_splitterr[index] = track_splitterr[index].replace(',"len":', ",");
                track_splitterr[index] = track_splitterr[index].replace(',"loop":', "m,");
                var num = index + 1;
                track_splitterr[index] = 'Track ' + num + track_splitterr[index];
                retStr[index_g] = track_splitterr[index];
                index_g++;
            }
            // console.log(track_splitterr);
        }

        if (json_spliterr[2] != '') {
            var route_spliterr = json_spliterr[2].split('},{');
            for (var index = 0; index < route_spliterr.length; index++) {
                route_spliterr[index] = route_spliterr[index].replace(']', "");
                route_spliterr[index] = route_spliterr[index].replace('[', "");
                route_spliterr[index] = route_spliterr[index].replace('}', "");
                route_spliterr[index] = route_spliterr[index].replace('{', "");
                route_spliterr[index] = route_spliterr[index].replace('"name":"', ",");
                route_spliterr[index] = route_spliterr[index].replace('","numPoints":', ",");
                route_spliterr[index] = route_spliterr[index].replace(',"len":', ",");
                route_spliterr[index] = route_spliterr[index].replace(',"loop":', "m,");
                var num = index + 1;
                route_spliterr[index] = 'Route ' + num + route_spliterr[index];
                retStr[index_g] = route_spliterr[index];
                index_g++;
            }
            // console.log(route_spliterr);
        }

    }
    // console.log(retStr);
    res.send({
        somethingElse: retStr
    });
});

app.get('/GPX_log_table', function (req, res) {
    fs.readdir(path.join(__dirname + '/uploads'), 'utf8', function (err, contents) {

        let retStr = [];
        var index = 0;
        contents.forEach(file => {
            var file_name = file;
            let gpxDoc = shared.createValidGPXdoc("./uploads/" + file_name, "./parser/bin/gpx.xsd");
            let valid = shared.validateGPXDoc(gpxDoc, "parser/bin/gpx.xsd");
            if (valid == true) {
                var tpr = shared.GPXtoJSON(gpxDoc);
                var tp2 = tpr.replace(/['"]+/g, '');
                // console.log(tp2);
                retStr[index] = tp2.replace('{version:', ",");
                // console.log(retStr[index]);
                retStr[index] = retStr[index].replace(',creator:', ",");
                retStr[index] = retStr[index].replace(',numWaypoints:', ",");
                retStr[index] = retStr[index].replace(',numRoutes:', ",");
                retStr[index] = retStr[index].replace(',numTracks:', ",");
                retStr[index] = retStr[index].replace('}', ",");
                retStr[index] = file + retStr[index];
                // console.log('->>>>' + retStr[index]);
                index++;
            }
        });
        // console.log(retStr);
        res.send({
            json_array: retStr
        });
    });
});

app.listen(portNum);
console.log('Running app at localhost: ' + portNum);


// const mysql = require('mysql2');

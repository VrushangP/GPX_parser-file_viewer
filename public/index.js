var table = document.getElementById("myTable");

var check1 = 0;
var check2 = 0;

var p = document.getElementsByTagName("P")[0];
// document.renameNode(p, null, "h1");
function new_route() {
  console.log('enter the route');
  var file = document.getElementById("file_select");
  var r_or_t = document.getElementById('route/track');
  var n = document.getElementById("waypoint_num");
  var r_name = document.getElementById("route_track_name");
  console.log('there are '+n.value + 'rows');

  var name = [];
  var lat = [];
  var lon = [];

  let e = "nameBox";
  let f = "latBox";
  let g = "lonBox";

  var i =0;
  let element;
  let element2;
  let element3;
  for (element = document.getElementById(e + i); typeof(element) != 'undefined' && element != null; i++) {
    // alert('Element exists!');
    var str = 'nameBox' + i;
    element = document.getElementById(str);
    if (typeof(element) != 'undefined' && element != null) {
      element2 = document.getElementById(f + i);
      element3 = document.getElementById(g + i);
      name[i] = element.value;
      lat[i] = element2.value;
      lon[i] = element3.value;
      console.log(name, lat, lon);
    } else {
      break;
    }
    // document.getElementById("blah").innerHTML = document.getElementById("blah").innerHTML + element.value + ' ';
  }
  console.log("starts here");
  console.log(r_name.value);
  var nm = r_name.value;
  console.log(name, lat, lon);

  jQuery.ajax({
    type: "get",
    url: "/append_route",
    dataType : 'json',
    data: {
      file: file.value,
      r_or_t: r_or_t.value,
      n: n.value,
      name: name,
      r_name: r_name.value,
      lat: lat,
      lon: lon
    },
    success: function(records){
      console.log('entered the jquery');
      var json_array = records.somethingElse;
      alert(json_array);
      // location.reload();

      // var table = document.getElementById("otherdata_table");
    },
    fail: function(error) {
      console.log("failed to load GPX Other Data Table");
    }
  });
  setInterval('location.reload()', 1000);

}



function add_waypoint_boxes() {

  var n = document.getElementById("waypoint_num");

  var dynamicTextBox1= "";
  var dynamicTextBox2= "";
  var dynamicTextBox3= "";

  for (var i = 0; i < n.value; i++) {
        dynamicTextBox1 += '<input class="form-control"  name = "DynamicTextBox"  id=  "nameBox'+i+'"  type="text" value = "' + n.value + '" />'; 
        dynamicTextBox2 += '<input class="form-control"  name = "DynamicTextBox"  id=  "latBox'+i+'"  type="text" value = "' + n.value + '" />'; 
        dynamicTextBox3 += '<input class="form-control"  name = "DynamicTextBox"  id=  "lonBox'+i+'"  type="text" value = "' + n.value + '" />'; 
  }

  console.log(dynamicTextBox1);
  document.getElementById("name_box").innerHTML = dynamicTextBox1;
  document.getElementById("lat_box").innerHTML = dynamicTextBox2;
  document.getElementById("lon_box").innerHTML = dynamicTextBox3;

}

function show_N_routes() {
  var file = document.getElementById("choose_file3");
  var sort = document.getElementById("order_select");
  var sort2 = document.getElementById("order_select2");
  var n = document.getElementById("show_N");
  var table = document.getElementById("sql_ROUTE3");
  document.getElementById("sql_ROUTE3").style.display = file.value != 'Select A File' ? 'block' : 'none';

  $("#sql_ROUTE3").find("tr:gt(0)").remove();

  jQuery.ajax({
    type: "get",
    url: "/print_N_routes",
    dataType : 'json',
    data: {
      file: file.value,
      order: sort.value,
      n: n.value,
      order2: sort2.value
    },
    success: function(records){
      var json_array = records.somethingElse;

      // var table = document.getElementById("otherdata_table");
      for (var i = 0; i < json_array.length && i < n.value; i++) {
        if (json_array[i] != '') {
          var row_spliterr = json_array[i].split(',');
          var row = table.insertRow(-1);
          var tb1 = row.insertCell(0);
          var tb2 = row.insertCell(1);
          var tb3 = row.insertCell(2);
          var tb4 = row.insertCell(3);

          tb1.innerHTML = row_spliterr[0];
          tb2.innerHTML = row_spliterr[1];
          tb3.innerHTML = row_spliterr[2];
          tb4.innerHTML = row_spliterr[3];
        }
      }
    },
    fail: function(error) {
      console.log("failed to load GPX Other Data Table");
    }
  });
}

function show_file_points() {
  var file = document.getElementById("choose_file2");
  var sort = document.getElementById("sort_select3");
  var table = document.getElementById("sql_POINT2");
  document.getElementById("sql_POINT2").style.display = file.value != 'Select A File' ? 'block' : 'none';

  $("#sql_POINT2").find("tr:gt(0)").remove();

  jQuery.ajax({
    type: "get",
    url: "/print_file_points",
    dataType : 'json',
    data: {
      file: file.value,
      sort: sort.value
    },
    success: function(records){
      var json_array = records.somethingElse;

      // var table = document.getElementById("otherdata_table");
      for (var i = 0; i < json_array.length; i++) {
        if (json_array[i] != '') {
          var row_spliterr = json_array[i].split(',');
          var row = table.insertRow(-1);
          var tb1 = row.insertCell(0);
          var tb2 = row.insertCell(1);
          var tb3 = row.insertCell(2);
          var tb4 = row.insertCell(3);
          var tb5 = row.insertCell(4);
          var tb6 = row.insertCell(5);

          tb1.innerHTML = row_spliterr[0];
          tb2.innerHTML = row_spliterr[1];
          tb3.innerHTML = row_spliterr[2];
          tb4.innerHTML = row_spliterr[3];
          tb5.innerHTML = row_spliterr[4];
          tb6.innerHTML = row_spliterr[5];
        }
      }
    },
    fail: function(error) {
      console.log("failed to load GPX Other Data Table");
    }
  });
}

function show_route_points() {
  var file = document.getElementById("route_selec");
  var table = document.getElementById("sql_POINT");
  document.getElementById("sql_POINT").style.display = file.value != 'Select A Route' ? 'block' : 'none';

  $("#sql_POINT").find("tr:gt(0)").remove();

  jQuery.ajax({
    type: "get",
    url: "/print_route_points",
    dataType : 'json',
    data: {
      file: file.value
    },
    success: function(records){
      var json_array = records.somethingElse;
      console.log(json_array);
      // var table = document.getElementById("otherdata_table");
      for (var i = 0; i < json_array.length; i++) {
        if (json_array[i] != '') {
          var row_spliterr = json_array[i].split(',');
          var row = table.insertRow(-1);
          var tb1 = row.insertCell(0);
          var tb2 = row.insertCell(1);
          var tb3 = row.insertCell(2);
          var tb4 = row.insertCell(3);
          var tb5 = row.insertCell(4);
          var tb6 = row.insertCell(5);

          tb1.innerHTML = row_spliterr[0];
          tb2.innerHTML = row_spliterr[1];
          tb3.innerHTML = row_spliterr[2];
          tb4.innerHTML = row_spliterr[3];
          tb5.innerHTML = row_spliterr[4];
          tb6.innerHTML = row_spliterr[5];
        }
      }
    },
    fail: function(error) {
      console.log("failed to load GPX Other Data Table");
    }
  });
}

function show_file_routes() {
  var file = document.getElementById("choose_file");
  var sort = document.getElementById("sort_select2");
  var table = document.getElementById("sql_ROUTE2");
  document.getElementById("sql_ROUTE2").style.display = file.value != 'Select A File' ? 'block' : 'none';

  $("#sql_ROUTE2").find("tr:gt(0)").remove();

  jQuery.ajax({
    type: "get",
    url: "/print_file_routes",
    dataType : 'json',
    data: {
      file: file.value,
      sort: sort.value
    },
    success: function(records){
      var json_array = records.somethingElse;

      // var table = document.getElementById("otherdata_table");
      for (var i = 0; i < json_array.length; i++) {
        if (json_array[i] != '') {
          var row_spliterr = json_array[i].split(',');
          var row = table.insertRow(-1);
          var tb1 = row.insertCell(0);
          var tb2 = row.insertCell(1);
          var tb3 = row.insertCell(2);
          var tb4 = row.insertCell(3);

          tb1.innerHTML = row_spliterr[0];
          tb2.innerHTML = row_spliterr[1];
          tb3.innerHTML = row_spliterr[2];
          tb4.innerHTML = row_spliterr[3];
        }
      }
    },
    fail: function(error) {
      console.log("failed to load GPX Other Data Table");
    }
  });
}

function show_all_routes() {
  var table = document.getElementById("sql_ROUTE");
  var file = document.getElementById("sort_select");
  // $("#sql_ROUTE").empty();
  $("#sql_ROUTE").find("tr:gt(0)").remove();
  jQuery.ajax({
    type: "get",
    url: "/print_all_routes",
    dataType : 'json',
    data: {
      data1: file.value
    },
    success: function(records){
      var json_array = records.somethingElse;
      console.log(json_array);
      // var table = document.getElementById("otherdata_table");
      for (var i = 0; i < json_array.length; i++) {
        if (json_array[i] != '') {
          var row_spliterr = json_array[i].split(',');
          var row = table.insertRow(-1);
          var tb1 = row.insertCell(0);
          var tb2 = row.insertCell(1);
          var tb3 = row.insertCell(2);
          var tb4 = row.insertCell(3);

          tb1.innerHTML = row_spliterr[0];
          tb2.innerHTML = row_spliterr[1];
          tb3.innerHTML = row_spliterr[2];
          tb4.innerHTML = row_spliterr[3];
        }
      }
    },
    fail: function(error) {
      console.log("failed to load GPX Other Data Table");
    }
  });
}

function display_query(query1, query2, query3, query4, query5 ,option) {

  document.getElementById(query1).style.display = option.value == 'Display all routes' ? 'block' : 'none';
  document.getElementById(query2).style.display = option.value == 'Display the routes from a specific file' ? 'block' : 'none';
  document.getElementById(query3).style.display = option.value == 'Display all points of a specific route' ? 'block' : 'none';
  document.getElementById(query4).style.display = option.value == 'Display all points from a specific file' ? 'block' : 'none';
  document.getElementById(query5).style.display = option.value == 'Display the N shortest/longest routes from a specific file.' ? 'block' : 'none';

  if (option.value == 'Display all points of a specific route') {
    jQuery.ajax({
      type: "get",
      url: "/retrieve_routes",
      dataType : 'json',
      data: {
      },
      success: function(records){
        var drop_menu = document.getElementById("route_selec");
        // console.log("eneters jq disp");
        var json_arr = records.somethingElse;
        for (var i = 0; i < json_arr.length; i++) {
          var option = document.createElement("option");
          option.value = json_arr[i];
          option.text = json_arr[i];
          drop_menu.add(option);
        }
      },
      fail: function(error) {
        console.log("failed log initiate login seqence");
      }
    });

  }

}

function DisplayDSStat() {
  jQuery.ajax({
    type: "get",
    url: "/disp_db",
    dataType : 'json',
    data: {
    },
    success: function(records){
      // console.log("eneters jq disp");
      var json_array = records.somethingElse;
      // console.log("out ->>>" + json_array);
      alert("FILE: "+json_array[0] +"\nROUTE: " +json_array[1] +"\nPOINT: " +json_array[2]);
      // console.log("leaving jq disp");
    },
    fail: function(error) {
      console.log("failed log initiate login seqence");
    }
  });
}

function ClearDB() {
  jQuery.ajax({
    type: "get",
    url: "/clear_db",
    dataType : 'json',
    data: {
    },
    success: function(records){
      // console.log("eneters jq disp");
      var json_array = records.somethingElse;
      // console.log("out ->>>" + json_array);
      alert("Database tables have been cleared");
      // console.log("leaving jq disp");
    },
    fail: function(error) {
      console.log("failed log initiate login seqence");
    }
  });
}

function store() {
  check2 = 1;
  var len = document.getElementById("file_select").length;
  console.log(len);
  if (len > 1) {
    jQuery.ajax({
      type: "get",
      url: "/store_db",
      dataType : 'json',
      data: {
      },
      success: function(records){
        var json_array = records.somethingElse;
      },
      fail: function(error) {
        console.log("failed log initiate login seqence");
      }
    });
  } else {
    alert("No files present to add to the database");
  }
}

function login() {
  check1 = 1;
  var userr = document.getElementById("username");
  var passs = document.getElementById("password");
  var datab = document.getElementById("server_name");
  console.log(userr.value);
  console.log(passs.value);
  console.log(datab.value);
  document.getElementById("insert here").innerHTML = userr.value + passs.value + datab.value;
  // inser.innerHTML = row_spliterr[0];
  // var file = document.getElementById("file_select");
  jQuery.ajax({
    type: "get",
    url: "/login_db",
    dataType : 'json',
    data: {
      hostName: "dursley.socs.uoguelph.ca",
      username: userr.value,
      password: passs.value,
      dataBase: datab.value
    },
    success: function(records){
      console.log("eneters jq");
      var json_array = records.somethingElse;

      console.log("leaving jq");
    },
    fail: function(error) {
      console.log("failed log initiate login seqence");
    }
  });
  // alter();
  // var tpr = file.value;
}

function Create_new() {
  var file_name = document.getElementById("new_GPX_name");
  // var ns = document.getElementById("new_ns");
  var ver = document.getElementById("new_version");
  var creator = document.getElementById("new_creator");

  jQuery.ajax({
    type: "get",
    url: "/GPX_newfile",
    dataType : 'json',
    data: {
      file_name: file_name.value,
      ver: ver.value,
      creator: creator.value
    },
    success: function(records){
      console.log("new file created");
      var json_array = records.somethingElse;
      alert(json_array);
    },
    fail: function(error) {
      console.log("failed to load GPX Other Data Table");
    }
  });
  // setInterval('location.reload()', 100);
}

function inbetween() {
  var file = document.getElementById("file_select");
  var tpr = file.value;
}

function rename_func(new_name) {
  var route_track = document.getElementById("rename_select");
  var file = document.getElementById("file_select");
  console.log(file.value + route_track.value + new_name.value);

  jQuery.ajax({
    type: "get",
    url: "/GPX_rename",
    dataType : 'json',
    data: {
      file_name: file.value,
      route_name: route_track.value,
      new_route_name: new_name.value
    },
    success: function(records){
      console.log(file.value + route_track.value + new_name.value);
      var json_array = records.somethingElse;
      alert(json_array);
    },
    fail: function(error) {
      console.log("failed to load GPX Other Data Table");
    }
  });
  setInterval('location.reload()', 100);
}

function rename(alter_name, route_track_object) {
  var tpr = route_track_object.value;
  document.getElementById(alter_name).style.display = route_track_object.value != 'empty' ? 'block' : 'none';
}

function otherData(alter_name, route_track_object) {
  var otherdata_table = document.getElementById("otherdata_table");
  var file = document.getElementById("file_select");
  otherdata_table.getElementsByTagName("tbody")[0].innerHTML = otherdata_table.rows[0].innerHTML;
  document.getElementById(alter_name).style.display = route_track_object.value != 'empty' ? 'block' : 'none';

  jQuery.ajax({
    type: "get",
    url: "/GPX_other_data",
    dataType : 'json',
    data: {
      file_name: file.value,
      route_name: route_track_object.value
    },
    success: function(records){
      var json_array = records.somethingElse;

      var table = document.getElementById("otherdata_table");
      for (var i = 0; i < json_array.length; i++) {
        if (json_array[i] != '') {
          var row_spliterr = json_array[i].split(',');
          var row = table.insertRow(-1);
          var tb1 = row.insertCell(0);
          var tb2 = row.insertCell(1);

          tb1.innerHTML = row_spliterr[0];
          tb2.innerHTML = row_spliterr[1];
        }
      }
    },
    fail: function(error) {
      console.log("failed to load GPX Other Data Table");
    }
  });
}

function new_row(alter_GPX, file_object) {
  var tpr = file_object.value;
  var mytbl = document.getElementById("table2");
  mytbl.getElementsByTagName("tbody")[0].innerHTML = mytbl.rows[0].innerHTML;
  $("#rename_select").empty();
  $("#otherdata_select").empty();
  document.getElementById(alter_GPX).style.display = file_object.value != 'Select A File' && check1 == 1 && check2 == 1 ? 'block' : 'none';
  // console.log(str + '   ' + tpr);
  jQuery.ajax({
    type: "get",
    url: "/GPX_view_table",
    dataType : 'json',
    data: {
      file_name: tpr
    },
    success: function(records){
      var tpr = file_object.value;
      var json_arr = records.somethingElse;

      var table = document.getElementById("table2");
      var drop_menu = document.getElementById("rename_select");
      var drop_menu2 = document.getElementById("otherdata_select");
      var option = document.createElement("option");
      var option2 = document.createElement("option");
      option.value = "empty";
      option.text = "select a route/track";
      option2.value = "empty";
      option2.text = "select a route/track";
      drop_menu.add(option);
      drop_menu2.add(option2);

      for (var i = 0; i < json_arr.length; i++) {
        var row_spliterr = json_arr[i].split(',');
        var row = table.insertRow(-1);
        var tb1 = row.insertCell(0);
        var tb2 = row.insertCell(1);
        var tb3 = row.insertCell(2);
        var tb4 = row.insertCell(3);
        var tb5 = row.insertCell(4);
        var option = document.createElement("option");
        option.value = row_spliterr[1];
        option.text = row_spliterr[1];
        drop_menu.add(option);
        var option2 = document.createElement("option");
        option2.value = row_spliterr[1];
        option2.text = row_spliterr[1];
        drop_menu2.add(option2);
        tb1.innerHTML = row_spliterr[0];
        tb2.innerHTML = row_spliterr[1];
        tb3.innerHTML = row_spliterr[2];
        tb4.innerHTML = row_spliterr[3];
        tb5.innerHTML = row_spliterr[4];
      }
      // jQuery('#blah').html("On page load, received string '"+data.somethingElse+"' from server");

    },
    fail: function(error) {
      console.log("failed to load GPX View Table");
    }
  });
}

jQuery(document).ready(function() {
    // On page-load AJAX Example
    jQuery.ajax({
      type: 'get',
      dataType: 'json',
      url: '/GPX_log_table',
      data: {
        content: 0
      },
      success: function(data) {
        var json_arr = [];
        json_arr = data.json_array;
        var table = document.getElementById("table");
        var drop_menu = document.getElementById("file_select");
        var drop_menu2 = document.getElementById("choose_file");
        var drop_menu3 = document.getElementById("choose_file2");
        var drop_menu4 = document.getElementById("choose_file3");

        for (var i = 0; i < json_arr.length; i++) {
          var row_spliterr = json_arr[i].split(',');
          var row = table.insertRow(-1);
          var tb1 = row.insertCell(0);
          var tb2 = row.insertCell(1);
          var tb3 = row.insertCell(2);
          var tb4 = row.insertCell(3);
          var tb5 = row.insertCell(4);
          var tb6 = row.insertCell(5);
          var option = document.createElement("option");
          option.value = row_spliterr[0];
          option.text = row_spliterr[0];
          drop_menu.add(option);
          var option2 = document.createElement("option");
          option2.value = row_spliterr[0];
          option2.text = row_spliterr[0];
          drop_menu2.add(option2);
          var option3 = document.createElement("option");
          option3.value = row_spliterr[0];
          option3.text = row_spliterr[0];
          drop_menu3.add(option3);
          var option4 = document.createElement("option");
          option4.value = row_spliterr[0];
          option4.text = row_spliterr[0];
          drop_menu4.add(option4);
          tb1.innerHTML = '<a href="'+row_spliterr[0]+'">'+row_spliterr[0]+'</a>';
          tb2.innerHTML = row_spliterr[1];
          tb3.innerHTML = row_spliterr[2];
          tb4.innerHTML = row_spliterr[3];
          tb5.innerHTML = row_spliterr[4];
          tb6.innerHTML = row_spliterr[5];
        }
      },
      fail: function(error) {
        console.log("failed to load GPX View Table");
      }
    });

    jQuery.ajax({
      type: 'get',            //Request type
      dataType: 'json',       //Data type - we will use JSON for almost everything
      url: '/endpoint1',   //The server endpoint we are connecting to
      data: {
          data1: "Value 1",
          data2: 1234.56
      },
        success: function (data) {
            console.log("success")
        },
        fail: function(error) {
            // Non-200 return, do something with error
            $('#blah').html("On page load, received error from server");
            console.log(error);
        }
    });

    // Event listener form example , we can use this instead explicitly listening for events
    // No redirects if possible
    $('#someform').submit(function(e){

        e.preventDefault();
        //Pass data to the Ajax call, so it gets passed to the server
        $.ajax({
            //Create an object for connecting to another waypoint
        });
    });
});

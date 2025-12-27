function doGet(e) { 
  return handleRequest(e);
}
function doPost(e) {
  return handleRequest(e);
}
function handleRequest(e) {
  var sheet = SpreadsheetApp.getActiveSpreadsheet().getActiveSheet();

  if (e.parameter.action == "read") {
    var data = sheet.getDataRange().getValues();
    return ContentService
      .createTextOutput(JSON.stringify(data))
      .setMimeType(ContentService.MimeType.JSON);
  } else {
    var ppm = parseFloat(e.parameter.ppm);
    var temp = parseFloat(e.parameter.temp);
    var hum = parseFloat(e.parameter.hum);
    sheet.appendRow([new Date(), ppm, temp , hum]);
    return ContentService.createTextOutput("Success");
  }
}
export async function assetToFloat(assetStr, precision) {
  if (typeof precision === "undefined") {
    precision = 4;
  }
  // console.log(typeof assetStr)
  // console.log(assetStr)
  return parseFloat(
    Math.round(
      parseFloat(assetStr.substring(0, assetStr.length - 4)) * 10 ** precision
    ) /
      10 ** precision
  ).toFixed(precision);
}

export async function roundAsset(assetStr, precision) {
  return assetToFloat(assetStr, precision) + " " + assetStr.split(" ").pop();
}

#' An artificial dataset with sudden edge shift around at entry 9.000
#' 
#' @docType data
#'
#' @usage data(ArtificialDistributionChange)
#'
#' @format A \code{"data.frame"} formatted for direct use within \code{"getMIDASscore()"}
#'
#' @keywords datasets
#'
#' @references None
#'
#' @source data.frame(src = rep(1,100000), dst = c(as.integer(rexp(n = 90000, rate = .65)) + 2, as.integer(abs(rnorm(10000, 8, .7))) + 1), times = unlist(lapply(c(1:1000), rep, times=100)))
#'
#' @examples
#' data(ArtificialDistributionChange)
#' plot(getMIDASScore(ArtificialDistributionChange))
"ArtificialDistributionChange"

#' Dataset provided by the original C++ implementation of MIDAS
#' 
#' @docType data
#'
#' @usage data(MIDASexample)
#'
#' @format A \code{data.frame} formatted for direct use within \code{"getMIDASscore()"}
#'
#' @keywords datasets
#'
#' @references Siddharth Bhatia, Bryan Hooi, Minji Yoon, Kijung Shin, Christos Faloutsos. AAAI 2020. (\href{https://www.comp.nus.edu.sg/~sbhatia/assets/pdf/midas.pdf}{AAAI})
#'
#' @source \href{https://github.com/bhatiasiddharth/MIDAS}{Github}
#'
#' @examples
#' data(MIDASexample)
#' plot(getMIDASScore(head(MIDASexample,10000)))
"MIDASexample"



params.alignment = "${baseDir}/data/test.fa"
params.output = "${baseDir}/results/"

// Channels containing sequences
if ( params.alignment ) {
  Channel
  .fromPath(params.alignment)
  .map { item -> [ item.baseName, item] }
  //.view()
  .set { aln }
}

process parseGaps {
    tag ""
    publishDir "${params.output}", mode: 'copy', overwrite: true  

    input:
      file(aln) from aln

    output:
     set file("resultF2G.gap"), file("resultG2F.fa") into parserOut

    script:
    """
    ${baseDir}/bin/gap
    """
}
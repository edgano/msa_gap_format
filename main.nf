


params.alignment = "${baseDir}/data/*.aln"
params.output = "${baseDir}/results/"

// Channels containing sequences
if ( params.alignment ) {
  Channel
  .fromPath(params.alignment)
  .map { item -> [ item.baseName, item] }
  .view()
  .set { alnCh }
}

process parseGaps {
    tag ""
    publishDir "${params.output}", mode: 'copy', overwrite: true  

    input:
    set val(id), file(aln) from alnCh

    output:
     set file(aln), file("resultF2G.gap"), file("resultG2F.fa"), file("${id}.out") into parserOut

    script:
    """
    ${baseDir}/bin/gap ${aln}

    echo "" >> ${aln}
    diff -B ${aln} resultG2F.fa >> ${id}.out
    """
}
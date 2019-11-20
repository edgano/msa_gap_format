#!/usr/bin/env nextflow

//params.alignment = "${baseDir}/results/alignments/*.dpa_1000.*.tree.aln"
params.alignment = "/users/cn/efloden/projects/dpa-benchfam-99k/results/alignments/*.dpa_1000.*.tree.aln"
params.output = "${baseDir}/results/benchfam"


log.info """\
         R E G R E S S I V E   M S A   A n a l y s i s  ~  version 0.1"
         ======================================="
         Input Alignments (ALN)                         : ${params.tfa}
         Output directory (DIRECTORY)                   : ${params.output}
         \
         """
         .stripIndent()


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
     set file(aln), file("${id}_F2G.gap"), file("${id}_G2F.fa"), file("${id}_diff.out") into parserOut

    script:
    """
    ${baseDir}/bin/gap ${aln}

    mv resultF2G.gap ${id}_F2G.gap
    mv resultG2F.fa ${id}_G2F.fa

    echo "" >> ${aln}
    diff -B ${aln} ${id}_G2F.fa >> ${id}_diff.out

    """
}
